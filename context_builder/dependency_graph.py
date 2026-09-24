from pathlib import Path
from typing import Dict, List
import re


class DependencyGraphBuilder:
    """Build an include dependency graph for AIForce-generated application files."""

    INCLUDE_PATTERN = re.compile(
        r'^\s*#\s*include\s*[<"]([^">]+)[">]'
    )

    def __init__(self, project_root: str = ".") -> None:
        self.project_root = Path(project_root).resolve()

        # AIForce-generated application directories.
        self.application_src = self.project_root / "code" / "src"
        self.application_inc = self.project_root / "code" / "inc"

        # Include paths used to resolve both application and platform headers.
        #
        # Platform headers are used only for resolving includes.
        # They are NOT added to the application dependency graph.
        self.include_paths = [
            self.application_inc,
            self.project_root / "firmware" / "Core" / "Inc",
            self.project_root
            / "firmware"
            / "Drivers"
            / "STM32F4xx_HAL_Driver"
            / "Inc",
            self.project_root / "firmware" / "Drivers" / "CMSIS" / "Include",
            self.project_root
            / "firmware"
            / "Drivers"
            / "CMSIS"
            / "Device"
            / "ST"
            / "STM32F4xx"
            / "Include",
        ]

    def _is_application_file(self, path: Path) -> bool:
        """Return True when the file belongs to the generated application."""

        resolved = path.resolve()

        return (
            resolved.is_relative_to(self.application_src)
            or resolved.is_relative_to(self.application_inc)
        )

    def _resolve_include(
        self,
        include_name: str,
        current_file: Path,
    ) -> Path | None:
        """Resolve an include against application and firmware include paths."""

        search_paths = [
            current_file.parent,
            *self.include_paths,
        ]

        for directory in search_paths:
            candidate = (directory / include_name).resolve()

            if candidate.exists():
                return candidate

        return None

    def _collect_includes(
        self,
        source_file: Path,
    ) -> List[str]:
        """Collect application-file include dependencies."""

        dependencies: List[str] = []

        try:
            source_text = source_file.read_text(
                encoding="utf-8",
                errors="ignore",
            )
        except OSError:
            return dependencies

        for line in source_text.splitlines():

            match = self.INCLUDE_PATTERN.match(line)

            if match is None:
                continue

            include_name = match.group(1)

            included_file = self._resolve_include(
                include_name,
                source_file,
            )

            if included_file is None:
                continue

            # Only AIForce-generated application files are included
            # in the dependency graph.
            if not self._is_application_file(included_file):
                continue

            # Store only the file name in the JSON representation.
            dependencies.append(included_file.name)

        return sorted(set(dependencies))

    def build(self) -> Dict[str, List[str]]:
        """Build the application dependency graph."""

        graph: Dict[str, List[str]] = {}

        application_files = sorted(
            [
                *self.application_src.glob("*.c"),
                *self.application_inc.glob("*.h"),
            ]
        )

        for file_path in application_files:

            # Store only the file name in the JSON representation.
            graph[file_path.name] = self._collect_includes(
                file_path
            )

        return graph
