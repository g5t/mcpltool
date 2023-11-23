def mcpl_tool_cli():
    import sys
    from mcpltool import mcpl_tool
    args = sys.argv[1:]
    mcpl_tool(args)


def particle_count_cli():
    from argparse import ArgumentParser
    from mcpltool import particle_count
    from pathlib import Path
    parser = ArgumentParser(description="Count particles in MCPL file")
    parser.add_argument("mcpl_file", help="MCPL file to count particles in")
    args = parser.parse_args()
    path = Path(args.mcpl_file)
    if not path.is_file():
        raise FileNotFoundError(args.mcpl_file)
    print(particle_count(args.mcpl_file))


def merge_cli():
    from argparse import ArgumentParser
    from mcpltool import merge
    parser = ArgumentParser(description="Merge MCPL files")
    parser.add_argument("output", help="Output MCPL file")
    parser.add_argument("input", nargs="+", help="Input MCPL files")
    args = parser.parse_args()
    merge(args.output, args.input)
