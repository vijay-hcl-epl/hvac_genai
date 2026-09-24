from pathlib import Path
from typing import Any, Dict, List, Set

from clang import cindex

from context_builder.engines.clang_engine import ClangEngine


class SharedStateBuilder:
    """Build a shared-state map for application-owned global variables."""

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

    def _parse_source(
        self,
        source_file: Path,
    ) -> cindex.TranslationUnit:
        """Parse an application source file."""

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

    def _collect_global_definitions(
        self,
        translation_units: List[cindex.TranslationUnit],
    ) -> Dict[str, Dict[str, Any]]:
        """Collect application-owned global variable definitions."""

        globals_map: Dict[str, Dict[str, Any]] = {}

        for translation_unit in translation_units:

            for cursor in translation_unit.cursor.walk_preorder():

                if cursor.kind != cindex.CursorKind.VAR_DECL:
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

                # Only file-scope variables are considered shared state.
                parent = cursor.semantic_parent

                if parent is None:
                    continue

                if parent.kind != cindex.CursorKind.TRANSLATION_UNIT:
                    continue

                globals_map[cursor.spelling] = {
                    "defined_in": definition_file.name,
                    "type": cursor.type.spelling,
                    "used_by": set(),
                }

        return globals_map

    def _collect_global_references(
        self,
        translation_units: List[cindex.TranslationUnit],
        globals_map: Dict[str, Dict[str, Any]],
    ) -> None:
        """Find application source files that reference shared globals."""

        global_names: Set[str] = set(
            globals_map.keys()
        )

        for translation_unit in translation_units:

            source_file = Path(
                translation_unit.spelling
            ).resolve()

            if not self._is_application_source(
                source_file
            ):
                continue

            source_name = source_file.name

            for cursor in translation_unit.cursor.walk_preorder():

                if cursor.kind != cindex.CursorKind.DECL_REF_EXPR:
                    continue

                referenced = cursor.referenced

                if referenced is None:
                    continue

                if referenced.kind != cindex.CursorKind.VAR_DECL:
                    continue

                variable_name = referenced.spelling

                if variable_name not in global_names:
                    continue

                # The defining file is already represented by
                # "defined_in". "used_by" contains only the
                # other application files that access the state.
                if source_name == globals_map[variable_name]["defined_in"]:
                    continue

                globals_map[variable_name]["used_by"].add(
                    source_name
                )

    def build(self) -> Dict[str, Dict[str, Any]]:
        """Build the application shared-state map."""

        translation_units: List[cindex.TranslationUnit] = []

        source_files = sorted(
            self.application_src.glob("*.c")
        )

        for source_file in source_files:

            translation_units.append(
                self._parse_source(source_file)
            )

        globals_map = self._collect_global_definitions(
            translation_units
        )

        self._collect_global_references(
            translation_units,
            globals_map,
        )

        result: Dict[str, Dict[str, Any]] = {}

        for name, data in sorted(
            globals_map.items()
        ):

            used_by = sorted(
                data["used_by"]
            )

            # Keep only genuinely shared state.
            #
            # A global is considered shared when at least
            # one other application source file accesses it.
            if not used_by:
                continue

            result[name] = {
                "defined_in": data["defined_in"],
                "type": data["type"],
                "used_by": used_by,
            }

        return result
