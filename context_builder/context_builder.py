import json
from pathlib import Path
from typing import Any, Dict

from context_builder.dependency_graph import DependencyGraphBuilder
from context_builder.symbol_ownership import SymbolOwnershipBuilder
from context_builder.interface_contracts import InterfaceContractsBuilder
from context_builder.call_graph import CallGraphBuilder
from context_builder.shared_state import SharedStateBuilder


class ProjectContextBuilder:
    """Build the complete project context for AIForce-generated code."""

    def __init__(
        self,
        project_root: str = ".",
        output_file: str = "context/project_context.json",
        clang_library: str = "/usr/lib/llvm-14/lib/libclang.so",
    ) -> None:
        self.project_root = Path(project_root).resolve()

        self.output_file = (
            self.project_root / output_file
        )

        self.clang_library = clang_library

    def build(self) -> Dict[str, Any]:
        """Build all supported project-context dimensions."""

        print("Building dependency graph...")
        dependency_graph = DependencyGraphBuilder(
            project_root=str(self.project_root)
        ).build()

        print("Building symbol ownership...")
        symbol_ownership = SymbolOwnershipBuilder(
            project_root=str(self.project_root),
            clang_library=self.clang_library,
        ).build()

        print("Building interface contracts...")
        interface_contracts = InterfaceContractsBuilder(
            project_root=str(self.project_root),
            clang_library=self.clang_library,
        ).build()

        print("Building call graph...")
        call_graph = CallGraphBuilder(
            project_root=str(self.project_root),
            clang_library=self.clang_library,
        ).build()

        print("Building shared state map...")
        shared_state_map = SharedStateBuilder(
            project_root=str(self.project_root),
            clang_library=self.clang_library,
        ).build()

        return {
            "dependency_graph": dependency_graph,
            "symbol_ownership": symbol_ownership,
            "interface_contracts": interface_contracts,
            "call_graph": call_graph,
            "shared_state_map": shared_state_map,
        }

    def write(self) -> Dict[str, Any]:
        """Build the project context and write it to JSON."""

        project_context = self.build()

        self.output_file.parent.mkdir(
            parents=True,
            exist_ok=True,
        )

        with self.output_file.open(
            "w",
            encoding="utf-8",
        ) as file:
            json.dump(
                project_context,
                file,
                indent=2,
                sort_keys=False,
            )

            file.write("\n")

        print(
            f"\nProject context written to: "
            f"{self.output_file}"
        )

        return project_context


def main() -> None:
    """Build project context from the repository root."""

    builder = ProjectContextBuilder()

    builder.write()


if __name__ == "__main__":
    main()
