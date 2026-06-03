# edsa

A collection of basic data structures for C.

## Installation

**Install [Emeralds](https://github.com/Oblivious-Oblivious/Emeralds) package manager**

## Compile the library

```sh
em list
em install
em build lib release
```

## Compile your code

```sh
# requires the edsa static library included in the export folder along with edsa.h
clang export/edsa.a your-code.c
```

## Documentation

- [allocator](docs/allocator.md)
- [boolean](docs/boolean.md)
- [fast-stack](docs/fast-stack.md)
- [file-handler](docs/file-handler.md)
- [hash](docs/hash.md)
- [linked-list](docs/linked-list.md)
- [min-priority-queue](docs/min-priority-queue.md)
- [preprocessor](docs/preprocessor.md)
- [stack](docs/stack.md)
- [string](docs/string.md)
- [table](docs/table.md)
- [vector](docs/vector.md)

## Contributing

1. Fork it (<https://github.com/Oblivious-Oblivious/edsa/fork>)
2. Create your feature branch (`git checkout -b my-new-feature`)
3. Commit your changes (`git commit -am 'Add some feature'`)
4. Push to the branch (`git push origin my-new-feature`)
5. Create a new Pull Request

## Contributors

- [atha](https://github.com/Oblivious-Oblivious) - creator and maintainer
