---
name: makefsdata
description: "Skill for the Makefsdata area of mh2030_demo. 26 symbols across 2 files."
---

# Makefsdata

26 symbols | 2 files | Cohesion: 85%

## When to Use

- Working with code in `middlewares/`
- Understanding how process_file, file_write_http_header, file_put_ascii work
- Modifying makefsdata-related functionality

## Key Files

| File | Symbols |
|------|---------|
| `middlewares/3rd_party/lwip-2.1.2/src/apps/http/makefsdata/makefsdata.c` | get_file_data, process_file_data, write_checksums, is_valid_char_for_c_var, fix_filename_for_c (+15) |
| `middlewares/3rd_party/lwip-2.1.2/src/apps/http/makefsdata/tinydir.h` | tinydir_open, tinydir_open_sorted, tinydir_readfile, tinydir_readfile_n, _tinydir_get_ext (+1) |

## Entry Points

Start here when exploring this area:

- **`process_file`** (Function) — `middlewares/3rd_party/lwip-2.1.2/src/apps/http/makefsdata/makefsdata.c:904`
- **`file_write_http_header`** (Function) — `middlewares/3rd_party/lwip-2.1.2/src/apps/http/makefsdata/makefsdata.c:1022`
- **`file_put_ascii`** (Function) — `middlewares/3rd_party/lwip-2.1.2/src/apps/http/makefsdata/makefsdata.c:1223`
- **`concat_files`** (Function) — `middlewares/3rd_party/lwip-2.1.2/src/apps/http/makefsdata/makefsdata.c:120`
- **`check_path`** (Function) — `middlewares/3rd_party/lwip-2.1.2/src/apps/http/makefsdata/makefsdata.c:121`

## Key Symbols

| Symbol | Type | File | Line |
|--------|------|------|------|
| `process_file` | Function | `middlewares/3rd_party/lwip-2.1.2/src/apps/http/makefsdata/makefsdata.c` | 904 |
| `file_write_http_header` | Function | `middlewares/3rd_party/lwip-2.1.2/src/apps/http/makefsdata/makefsdata.c` | 1022 |
| `file_put_ascii` | Function | `middlewares/3rd_party/lwip-2.1.2/src/apps/http/makefsdata/makefsdata.c` | 1223 |
| `concat_files` | Function | `middlewares/3rd_party/lwip-2.1.2/src/apps/http/makefsdata/makefsdata.c` | 120 |
| `check_path` | Function | `middlewares/3rd_party/lwip-2.1.2/src/apps/http/makefsdata/makefsdata.c` | 121 |
| `main` | Function | `middlewares/3rd_party/lwip-2.1.2/src/apps/http/makefsdata/makefsdata.c` | 178 |
| `tinydir_open` | Function | `middlewares/3rd_party/lwip-2.1.2/src/apps/http/makefsdata/tinydir.h` | 217 |
| `tinydir_open_sorted` | Function | `middlewares/3rd_party/lwip-2.1.2/src/apps/http/makefsdata/tinydir.h` | 219 |
| `tinydir_readfile` | Function | `middlewares/3rd_party/lwip-2.1.2/src/apps/http/makefsdata/tinydir.h` | 226 |
| `tinydir_readfile_n` | Function | `middlewares/3rd_party/lwip-2.1.2/src/apps/http/makefsdata/tinydir.h` | 228 |
| `_tinydir_get_ext` | Function | `middlewares/3rd_party/lwip-2.1.2/src/apps/http/makefsdata/tinydir.h` | 235 |
| `process_sub` | Function | `middlewares/3rd_party/lwip-2.1.2/src/apps/http/makefsdata/makefsdata.c` | 434 |
| `_tinydir_dirent_buf_size` | Method | `middlewares/3rd_party/lwip-2.1.2/src/apps/http/makefsdata/tinydir.h` | 771 |
| `get_file_data` | Function | `middlewares/3rd_party/lwip-2.1.2/src/apps/http/makefsdata/makefsdata.c` | 531 |
| `process_file_data` | Function | `middlewares/3rd_party/lwip-2.1.2/src/apps/http/makefsdata/makefsdata.c` | 629 |
| `write_checksums` | Function | `middlewares/3rd_party/lwip-2.1.2/src/apps/http/makefsdata/makefsdata.c` | 653 |
| `is_valid_char_for_c_var` | Function | `middlewares/3rd_party/lwip-2.1.2/src/apps/http/makefsdata/makefsdata.c` | 691 |
| `fix_filename_for_c` | Function | `middlewares/3rd_party/lwip-2.1.2/src/apps/http/makefsdata/makefsdata.c` | 702 |
| `register_filename` | Function | `middlewares/3rd_party/lwip-2.1.2/src/apps/http/makefsdata/makefsdata.c` | 740 |
| `is_ssi_file` | Function | `middlewares/3rd_party/lwip-2.1.2/src/apps/http/makefsdata/makefsdata.c` | 833 |

## Connected Areas

| Area | Connections |
|------|-------------|
| Ppp | 2 calls |
| Http | 1 calls |

## How to Explore

1. `context({name: "process_file"})` — see callers and callees
2. `query({query: "makefsdata"})` — find related execution flows
3. Read key files listed above for implementation details
