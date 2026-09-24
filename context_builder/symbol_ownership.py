from pathlib import Path
from typing import Dict

from clang import cindex

from context_builder.engines.clang_engine import ClangEngine


class SymbolOwnershipBuilder:
    """Build ownership information for application-defined functions."""

    def __init__(
        self,
        project_root: str = ".",
        clang_library: str = "/usr/lib/llvm-14/lib/libclang.so",
    ) -> None:
        self.project_root = Path(project_root).resolve()

        self.application_src = self.project_root / "code" / "src"
        self.application_inc = self.project_root / "code" / "inc"

        self.include_paths = [
            self.application_inc,
            self.project_root / "firmware" / "Core" / "Inc",
            self.project_root
            / "firmware"
            / "Drivers"
            / "STM32F4xx_HAL_Driver"
            / "Inc",
            self.project_root
            / "firmware"
            / "Drivers"
            / "CMSIS"
            / "Include",
            self.project_root
            / "firmware"
            / "Drivers"
            / "CMSIS"
            / "Device"
            / "ST"
            / "STM32F4xx"
            / "Include",
        ]

        self.engine = ClangEngine(clang_library)

    def _is_application_source(self, path: Path) -> bool:
        """Return True when a file belongs to code/src."""

        try:
            return path.resolve().is_relative_to(
                self.application_src
            )
        except FileNotFoundError:
            return False

    def _parse_source(self, source_file: Path) -> cindex.TranslationUnit:
        """Parse an application source file using the STM32 build context."""

        return self.engine.parse(
            str(source_file),
            include_paths=[
                str(path)
                for path in self.include_paths
            ],
            extra_args=[
                "-DSTM32F407xx",
            ],
        )

    def _collect_functions(
        self,
        translation_unit: cindex.TranslationUnit,
    ) -> Dict[str, str]:
        """Collect application-defined function ownership."""

        ownership: Dict[str, str] = {}

        for cursor in translation_unit.cursor.walk_preorder():

            if cursor.kind != cindex.CursorKind.FUNCTION_DECL:
                continue

            if not cursor.is_definition():
                continue

            if cursor.location.file is None:
                continue

            definition_file = Path(
                cursor.location.file.name
            ).resolve()

            if not self._is_application_source(
                definition_file
            ):
                continue

            ownership[cursor.spelling] = definition_file.name

        return ownership

    def build(self) -> Dict[str, Dict[str, str]]:
        """Build symbol ownership for application-defined functions."""

        functions: Dict[str, str] = {}

        source_files = sorted(
            self.application_src.glob("*.c")
        )

        for source_file in source_files:

            translation_unit = self._parse_source(
                source_file
            )

            functions.update(
                self._collect_functions(
                    translation_unit
                )
            )

        return {
            "functions": dict(
                sorted(functions.items())
            )
        }
