from importlib.metadata import version, PackageNotFoundError

try:
    __version__ = version("mcpltool")
except PackageNotFoundError:
    # package is not installed
    pass

from ._mcpltool_impl import mcpl_tool, particle_count, merge

__all__ = ["mcpl_tool", "particle_count", "merge"]
