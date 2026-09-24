from pathlib import Path
from typing import Optional

from clang import cindex


class ClangEngine:
    """Common Clang AST parsing engine for the project context builder."""

    _initialized = False

    def __init__(
        self,
        clang_library: str = "/usr/lib/llvm-14/lib/libclang.so",
    ) -> None:
        self.clang_library = clang_library

        if not Path(self.clang_library).exists():
            raise FileNotFoundError(
                f"libclang library not found: {self.clang_library}"
            )

        if not ClangEngine._initialized:
            cindex.Config.set_library_file(
                self.clang_library
            )
            ClangEngine._initialized = True

        self.index = cindex.Index.create()

    def parse(
        self,
        source_file: str,
        include_paths: Optional[list[str]] = None,
        extra_args: Optional[list[str]] = None,
    ) -> cindex.TranslationUnit:
        """Parse one C/C++ source or header file."""

        args: list[str] = [
            "-x",
            "c",
            "-std=c11",
        ]

        if include_paths:
            for include_path in include_paths:
                args.append(f"-I{include_path}")

        if extra_args:
            args.extend(extra_args)

        return self.index.parse(
            source_file,
            args=args,
        )
