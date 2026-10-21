# Compiling the recovered host source

`tooling/build-recovered-host.cmd` initializes the installed VS 2022 Build Tools,
compiles each recovered module as C11 with `/W4 /WX /O2`, then links the objects
into `tools/recovered-host/nocturne_recovered.dll`. This is the host behavior-test
build. PS2 compiler, linking and binary matching remain separate work.

The compiler reads `tooling/recovered-host.rsp`; LINK reads
`tooling/recovered-host-link.rsp`. Both lists use one argument per line so the
growing module/export list does not exceed the Windows command-line limit.
The compiler and linker are invoked separately. CL's `/link` applies only to
the remainder of its physical command-file line, and LINK command files cannot
nest. These constraints are documented by Microsoft in
[CL command files](https://learn.microsoft.com/en-us/cpp/build/reference/cl-command-files?view=msvc-170)
and [LINK command files](https://learn.microsoft.com/en-us/cpp/build/reference/linking?view=msvc-170).

The canonical validation report hashes both response files, the wrapper,
bindings, recovered source, fixture generators and adapters. Changing a build
input requires fresh validation before the progress index counts the source
as currently verified.
