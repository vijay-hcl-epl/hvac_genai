from pathlib import Path
from typing import Dict, List, Set

from clang import cindex

from context_builder.engines.clang_engine import ClangEngine


class CallGraphBuilder:
    """Build a call graph for application-owned functions."""

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
        """Return True when the file belongs to code/src."""

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

    def _collect_application_functions(
        self,
        translation_units: List[cindex.TranslationUnit],
    ) -> Set[str]:
        """Collect names of all application-owned functions."""

        functions: Set[str] = set()

        for translation_unit in translation_units:

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

                functions.add(cursor.spelling)

        return functions

    def _collect_calls(
        self,
        function_cursor: cindex.Cursor,
        application_functions: Set[str],
    ) -> List[str]:
        """Collect application-owned functions called by one function."""

        calls: Set[str] = set()

        for cursor in function_cursor.walk_preorder():

            if cursor.kind != cindex.CursorKind.CALL_EXPR:
                continue

            referenced = cursor.referenced

            if referenced is None:
                continue

            if referenced.kind != cindex.CursorKind.FUNCTION_DECL:
                continue

            function_name = referenced.spelling

            if function_name not in application_functions:
                continue

            calls.add(function_name)

        return sorted(calls)

    def _collect_function_calls(
        self,
        translation_unit: cindex.TranslationUnit,
        application_functions: Set[str],
    ) -> Dict[str, List[str]]:
        """Collect calls made by application-defined functions."""

        call_graph: Dict[str, List[str]] = {}

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

            function_name = cursor.spelling

            call_graph[function_name] = self._collect_calls(
                cursor,
                application_functions,
            )

        return call_graph

    def build(self) -> Dict[str, List[str]]:
        """Build the application call graph."""

        translation_units: List[cindex.TranslationUnit] = []

        source_files = sorted(
            self.application_src.glob("*.c")
        )

        for source_file in source_files:

            translation_units.append(
                self._parse_source(source_file)
            )

        application_functions = (
            self._collect_application_functions(
                translation_units
            )
        )

        call_graph: Dict[str, List[str]] = {}

        for translation_unit in translation_units:

            call_graph.update(
                self._collect_function_calls(
                    translation_unit,
                    application_functions,
                )
            )

        return dict(sorted(call_graph.items()))
