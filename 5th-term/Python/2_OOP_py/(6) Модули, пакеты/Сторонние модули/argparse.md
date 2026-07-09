
- https://docs.python.org/3.10/howto/argparse.html

### How It Works

`argparse` works by creating an `ArgumentParser` object, which defines what arguments the program requires. These arguments can be positional (required and ordered) or optional (with flags). The parser then parses the command-line input according to these definitions and provides the parsed values for use in the program.

### Available Operations and Methods

Some of the key methods of the `argparse.ArgumentParser` class include:

- ArgumentParser()
- add_parser()
- add_subparsers()
- `add_argument()`: Defines a new argument.
- `parse_args()`: Parses the command-line arguments.
- `print_help()`: Prints a help message.
- `print_usage()`: Prints a usage message.

 > ***please provide signature for these methods and explain it on examples!*** ***this is necessary prompt for new libs***
 

### Connected Terms

- **Positional arguments**: Required arguments that appear in a specific order.
- **Optional arguments**: Arguments that are not required and typically have flags (e.g., `-h` or `--help`).
- **Flags**: Symbols used to denote optional arguments.

### Deep Technical Features

- **Subparsers**: Allow defining sub-commands for complex applications.
- **Argument groups**: Group related arguments together for better organization and help messages.
- **Mutually exclusive groups**: Ensure that certain arguments cannot be used together.



### Examples

1. **Basic Example**

```python
import argparse

parser = argparse.ArgumentParser(description="A simple argument parser example.")
parser.add_argument('name', type=str, help="Your name")
parser.add_argument('--age', type=int, help="Your age", default=25)
args = parser.parse_args()

print(f"Hello, {args.name}! You are {args.age} years old.")




```
```
what is that signature in argparse add_argument ?

1) object ArgumentParser -> created.
- this object contains description? what is this object signature?

2) add_argument() -> what is that signature
3) parse_args() -> what it does? is that analogue for print? for int(input())?
```


2. **Using Optional Arguments**

```python
import argparse

parser = argparse.ArgumentParser(description="Optional arguments example.")
parser.add_argument('--verbose', action='store_true', help="Increase output verbosity")
args = parser.parse_args()


# where it appears? is it passed as an argument or flag? so what is verbose?
if args.verbose: 
    print("Verbose mode is on")
else:
    print("Verbose mode is off")

```



3. **Advanced Example with Subparsers**

```python
import argparse

parser = argparse.ArgumentParser(description="Subparsers example.")
subparsers = parser.add_subparsers(dest='command')

# Subparser for the "greet" command
greet_parser = subparsers.add_parser('greet', help="Greet someone")
greet_parser.add_argument('name', type=str, help="Name of the person to greet")

# Subparser for the "farewell" command
farewell_parser = subparsers.add_parser('farewell', help="Say farewell to someone")
farewell_parser.add_argument('name', type=str, help="Name of the person to say farewell to")

args = parser.parse_args()

if args.command == 'greet':
    print(f"Hello, {args.name}!")
elif args.command == 'farewell':
    print(f"Goodbye, {args.name}!")

```


> what are other available commands instead of greet and farewell?
> what do they do?
> or it is custom?
> okay so what is the first argument in that signature? the type, the "name" for parser?





