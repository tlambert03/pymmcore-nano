# pymmcore-nano

Experimental python bindings for CMMCore using nanobind.

## Clone repo

```sh
git clone https://github.com/pymmcore-plus/pymmcore-nano.git
git submodule update --init
```

## Setup dev environment (editable install)

Make sure you have uv installed: <https://docs.astral.sh/uv/getting-started/installation/>

This project uses `just` as a task runner.
If you have `just` installed (e.g. `brew install just`), you can fully setup the project with:

```sh
just install
```

If you prefer not to install `just` globally, you can install it with the rest of the
project dependencies using uv.  Then activate the environment and call `just install`

```sh
uv sync --no-install-project
. .venv/bin/activate  # Windows: .venv\Scripts\activate
just install
```

### test

Regardless of whether the environment is active, you can run:

```sh
just test
# or
just test-cov
```

or, if the environment is active:

```sh
pytest
```
