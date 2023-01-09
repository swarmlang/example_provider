# `swarmlang/example_provider`

This repo contains an example implementation of an [external runtime provider](https://github.com/swarmlang/swarm/blob/main/docs/vm/external-providers.md) for the Swarm VM.

This provider adds a single new function, `f:HELLO_WORLD`, which returns a `p:STRING`.

## Setup & Build

To build this provider, you will need both this source code and the Swarm source. Place them in this hierarchy:

```text
some_parent_dir/
 |- swarm/
 |- example_provider/
```

Then, run `make` in this repo to build the provider module, `example_provider.so`.


## Use

To call it:
```text
$l:hi <- call f:HELLO_WORLD
out $l:hi
```

To run it:
```shell
swarmc --external-provider example_provider.so [...]
```
