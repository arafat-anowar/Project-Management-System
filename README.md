# Project Management System

## 1. Project Overview

This is a terminal-based Project Management System written in C for Windows (it depends on `windows.h` and `conio.h` and is not portable as-is to other platforms). The system provides:

- User registration, login, logout, and password change (via email + a fixed security question)
- Per-user project CRUD (create/update/delete/view/search) with priority and status
- Per-user task CRUD (create/update/delete/view/search), scoped to a parent project
- Automatic project status transitions driven by the state of a project's tasks
- Automatic task cancellation propagation when a parent project is cancelled
- Priority-based sorting of projects and tasks (Cancelled/Completed items excluded from the sorted view)
- Eight report screens (four project reports, four task reports)
- A live clock and Unicode box-drawing terminal UI with fixed-coordinate cursor positioning
- Plain CSV files as the persistence layer (no database engine, no encryption/hashing)

All persistent data is stored as CSV text files under a `database` directory located one level above the executable (`..\database\`, i.e. relative to the working directory the program is run from).

Source code is the authority for everything in this document. Where the implementation is unusual, incomplete, or internally inconsistent, that behavior is described as-is rather than corrected — see **Section 19, Known Source-Level Inconsistencies**.

---

## 2. Technology / Environment

- **Language:** C
- **Target platform:** Windows only. Uses `windows.h` (`CreateDirectory`, `CONSOLE_SCREEN_BUFFER_INFO`, `SetConsoleCursorPosition`, `SetConsoleOutputCP`, `_beginthread`), `conio.h` (`getch`/`_getch`), and `process.h`.
- **Storage:** Flat CSV files, read/written with `fopen`/`fgets`/`fprintf`/`strtok`. No SQL, no external database library.
- **Build:** No build script/Makefile is included in the supplied source. `main.c` is a single entry point (`int main()` → `main_menu()`).
- **Character set:** The UI draws its borders using Unicode box-drawing characters (`╔ ═ ╗ ║ ╠ ╣ ╚ ╝`), and `init_console()` sets the console input/output code page to UTF‑8 (`CP_UTF8`) on Windows.

---

## 3. Project Structure

### 3.1 Source files

```text
Project Management System
│
├── main.c                  — program entry point (calls main_menu())
│
├── Authentication Module
│   ├── auth.h
│   └── auth.c
│
├── Project Management Module
│   ├── project.h
│   └── project.c
│
├── Task Management Module
│   ├── task.h
│   └── task.c
│
├── Reporting Module
│   ├── report.h
│   └── report.c
│
├── Utility Module
│   ├── utility.h
│   └── utility.c
│
└── User Interface Module
    ├── ui.h
    └── ui.c
```

Each header contains macros, structures, and function prototypes for its module. Each `.c` file contains only that module's implementations (the UI drawing/menu code for every module, however, all lives in `ui.c`, not in the module's own `.c` file — see Section 17).

### 3.2 Runtime file/directory layout

Relative to the working directory the executable is launched from:

```text
..\database\
├── userDBS.csv              (global — all registered users' profile info)
├── credentialDBS.csv        (global — all registered users' login credentials)
├── tmp_credentialDBS.csv    (transient — used while rewriting credentialDBS.csv)
├── log.csv                  (global — holds the currently logged-in username, one line)
│
└── <username>\                          (created at registration)
    ├── projectsDBS.csv                  (this user's projects)
    ├── tmp_projectsDBS.csv              (transient — used while rewriting projectsDBS.csv)
    ├── taskDBS.csv                      (this user's tasks, flat, includes unique_id)
    ├── tmp_task.csv                     (transient — used while rewriting taskDBS.csv)
    ├── sort_project.csv                 (this user's projects, priority-sorted, active only)
    ├── sort_task.csv                    (this user's tasks, priority-sorted, active only)
    └── Projects\                        (created at registration)
        ├── <lowercased project name>.csv    (per-project task list, no unique_id column)
        └── tmp_task.csv                     (transient — used while rewriting a per-project task file)
```

`userDBS.csv`, `credentialDBS.csv`, `tmp_credentialDBS.csv`, and `log.csv` are shared across all users and always accessed via the literal paths `..\database\userDBS.csv`, `..\database\credentialDBS.csv`, `..\database\tmp_credentialDBS.csv`, `..\database\log.csv`. Every other database file is per-user and its path is built at runtime by `get_path()` (see Section 6).

---

## 4. Application Flow

### 4.1 Main menu (before login)

```text
MAIN MENU
│
├── [1] Register             → create_user()
├── [2] Login                → login()
├── [3] Forgot Password      → change_password()
└── [ESC] Exit               → exit(1)
```

`main_menu()` runs in an infinite `while(1)` loop; each successful branch (`create_user`, `login`, `change_password`) returns control back to the same loop, which redraws the menu. Only `ESC` terminates the process (`exit(1)`).

### 4.2 Dashboard (after login)

```text
DASHBOARD
│
├── [1] Project Management   → project_management_dashboard()
├── [2] Task Management      → task_management_dashboard()
├── [3] Reports              → report_dashboard()
├── [4] Search                → search_dashboard()
├── [5] Profile               → view_profile()
└── [ESC] Logout               → logout(); return
```

`dashboard()` calls `sort_projects()` and `sort_tasks()` exactly **once**, immediately upon entry (before its own `while(1)` loop starts) — not on every redraw. `sort_projects()` internally triggers all of the automatic status-synchronization logic (Section 11), so logging in always brings project/task statuses up to date once. Subsequent automatic re-syncs during the same session only happen when the user re-enters **Project Management** (see Section 11.4), because `project_management_dashboard()` calls `sort_projects()` again at the top of its own loop on every redraw; `task_management_dashboard()` only calls `sort_tasks()` (which does **not** run the status-sync functions).

### 4.3 Sub-menus

```text
PROJECT MANAGEMENT                    TASK MANAGEMENT
├── [1] Create Project                ├── [1] Create Task
├── [2] Update Project                ├── [2] Update Task
├── [3] Delete Project                ├── [3] Delete Task
├── [4] View All Projects             ├── [4] View All Tasks
├── [5] Search Project                ├── [5] View Tasks by Name
├── [6] View Projects by Status       ├── [6] View Tasks by Project
├── [7] View Projects by Priority     ├── [7] View Tasks by Status
└── [ESC] Back                        ├── [8] View Tasks by Priority
                                       └── [ESC] Back

REPORTS                               SEARCH
├── [1] Project Summary Report        ├── [1] Search Project by ID or Name
├── [2] Project Progress Report       ├── [2] Search Task by Name
├── [3] Overdue Projects Report       ├── [3] (unlabeled — see Sec. 19.3)
├── [4] High Priority Projects Report ├── [4] (unlabeled — see Sec. 19.3)
├── [5] Task Summary Report           └── [ESC] Back → dashboard()
├── [6] Overdue Tasks Report
├── [7] High Priority Tasks Report
├── [8] Pending / Active Tasks Report
└── [ESC] Back
```

---

## 5. Data Structures

### 5.1 Authentication (`auth.h`)

```c
// used for login input
struct l_account
{
    char user_name_or_email[MAX_USERNAME_OR_EMAIL_LENGTH]; // 30
    char user_pass[MAX_PASSWORD_LENGTH];                    // 30
};

// used for registration input and for reading credentialDBS.csv / userDBS.csv rows
struct r_account
{
    char id[MAX_ID_LENGTH];                       // 20
    char name[MAX_NAME_LENGTH];                    // 30
    char email[MAX_EMAIL_LENGTH];                  // 30
    char phone[MAX_PHONE_FIELD_LENGTH];            // 13
    char user_name[MAX_USERNAME_LENGTH];           // 30
    char pass[MAX_PASSWORD_LENGTH];                // 30
    char security_question[MAX_SECURITY_QUESTION_LENGTH]; // 15
    char role[MAX_ROLE_LENGTH];                    // 20
    char login_status[MAX_LOGIN_STATUS_LENGTH];    // 20
};

// used for change-password input
struct account
{
    char email[MAX_EMAIL_LENGTH];
    char security_question[MAX_SECURITY_QUESTION_LENGTH];
    char new_pass[MAX_PASSWORD_LENGTH];
};
```

Note: `struct r_account` has 9 fields, but `userDBS.csv` only ever stores 5 of them (`id, name, email, phone, role`) and `credentialDBS.csv` stores a different 6 (`id, user_name, email, pass, security_question, login_status`) — the struct is a superset used as scratch space by both files' read/write code, not a 1:1 mirror of either file.

### 5.2 Project (`project.h`)

```c
struct p_details
{
    char id[PROJECT_ID_SIZE];
    char name[PROJECT_ID_OR_NAME_SIZE];
    char category[PROJECT_CATEGORY_SIZE];
    char description[PROJECT_DESCRIPTION_SIZE];
    char priority[PROJECT_PRIORITY_SIZE];
    char status[PROJECT_STATUS_SIZE];
    char start_date[PROJECT_START_DATE_SIZE];
    char end_date[PROJECT_END_DATE_SIZE];
    char created_by[20];
};
```

### 5.3 Task (`task.h`)

```c
struct t_details
{
    int  unique_id;
    char task_id[TASK_ID_SIZE];             // 15
    char project_id[TASK_PROJECT_ID_SIZE];  // 15
    char name[TASK_NAME_SIZE];              // 50
    char description[TASK_DESCRIPTION_SIZE];// 200
    char priority[TASK_PRIORITY_SIZE];      // 30
    char status[TASK_STATUS_SIZE];          // 30
    char start_date[TASK_START_DATE_SIZE];  // 15
    char end_date[TASK_END_DATE_SIZE];      // 15
    char created_by[20];
};
```

`unique_id` is the only field that does not appear in the per-project task CSV files (see Section 6.4).

---

## 6. Database and File System

All record fields below are listed in the exact order they are written/read (`strtok` calls occur in this order in every function except the three noted in Section 19.1).

### 6.1 `userDBS.csv` (global)

| Field | Source |
|---|---|
| id | `struct r_account.id` |
| name | `.name` |
| email | `.email` |
| phone | `.phone` (10 raw digits, no `+880` prefix — see 19.7) |
| role | `.role` (always `"Individual"`, see `DEFAULT_ROLE_NAME`) |

- **Created by:** never explicitly created; opened with `FILE_MODE_APPEND` by `create_user()`, which will create it if missing.
- **Written by:** `create_user()` (append, one row per registration). No function ever updates or removes a row.
- **Read by:** `generate_user_id()`, `view_profile()`.

### 6.2 `credentialDBS.csv` (global)

| Field | Source |
|---|---|
| id | matches the corresponding `userDBS.csv` row's id |
| username | `.user_name` |
| email | `.email` |
| password | `.pass` (plain text — not hashed) |
| security_question | the user's typed answer to the fixed prompt "What Is Your Favourite Food" (not the question text itself, only the answer) |
| login_status | `"login"` or `"logout"` |

- **Written by:** `create_user()` (append, new row with `login_status = "logout"`); `change_login_status()` (rewrite-all, updates one row's `login_status`); `change_password()` (rewrite-all, updates one row's password).
- **Read by:** `validate_user_name()`, `validate_email()`, `password_verify()`, `change_login_status()`, `change_password()`.
- **Rewrite pattern:** every write to this file follows: read `credentialDBS.csv` line by line → write every row (modified or not) to `tmp_credentialDBS.csv` → `remove(credentialDBS.csv)` → `rename(tmp_credentialDBS.csv, credentialDBS.csv)`.

### 6.3 `log.csv` (global, single-session marker)

Holds at most one line: the username of the currently logged-in user.

- **Written by:** `password_verify()` — this function opens `log.csv` in `FILE_MODE_WRITE` (which truncates it) *unconditionally*, at the start of every login attempt, before the credential match is evaluated. If the login attempt fails, the file is left empty; only on a successful match is the matched username written into it. **A failed login attempt therefore always clears whichever user was previously "logged in" according to this file.** `logout()` also opens it in write mode to clear it.
- **Read by:** `get_user_name()` (returns the first line, used everywhere a "current user" is needed), `header_screen()` (only checks whether the file is non-empty, to decide which time/date footer to draw), `view_profile()`.
- Because there is a single global `log.csv`, the system supports only one "current" logged-in user at a time on a given install — it is not a per-session token.

### 6.4 Per-user `projectsDBS.csv`

Path: `..\database\<username>\projectsDBS.csv`

| # | Field |
|---|---|
| 1 | id (e.g. `P1001`) |
| 2 | name |
| 3 | category |
| 4 | description |
| 5 | priority (`High` / `Medium` / `Low`) |
| 6 | status (`Created` / `In Progress` / `Completed` / `Cancelled`) |
| 7 | start_date (`YYYY-MM-DD`) |
| 8 | end_date (`YYYY-MM-DD`) |
| 9 | created_by (username) |

- **Created by:** `create_directories()` at registration (empty file).
- **Written by:** `create_project()` (append); `update_project()`, `delete_project()`, `update_cancelled_project_tasks()` (no — this one only touches tasks), `update_created_project_status()`, `update_project_status_by_tasks()` (all four of the latter rewrite-all via a temp file + rename).
- **Read by:** every project-listing/search/report/sort function.

### 6.5 Per-user `taskDBS.csv` (main, cross-project)

Path: `..\database\<username>\taskDBS.csv`

| # | Field |
|---|---|
| 1 | unique_id (integer, globally unique per user, starts at `10001`) |
| 2 | task_id (e.g. `T1001` — **only unique within its own project**, see Section 12.4) |
| 3 | project_id |
| 4 | name |
| 5 | description |
| 6 | priority |
| 7 | status (`Created` / `In Progress` / `Completed` / `Cancelled`) |
| 8 | start_date |
| 9 | end_date |
| 10 | created_by |

- **Created by:** `create_directories()` at registration (empty file).
- **Written by:** `create_task()` (append); `update_task()`, `delete_task()`, `update_cancelled_project_tasks()`, `update_project_status_by_tasks()` (indirectly, by reading it — it does not write it), `delete_project()` (rewrite-all to drop tasks of the deleted project) — all rewrite-all patterns use a temp file + rename.
- **Read by:** every task-listing/search/report/sort function and the three project-status-sync functions.

### 6.6 Per-project task file, `Projects\<lowercased project name>.csv`

Path: `..\database\<username>\Projects\<project name, lowercased>.csv`

| # | Field |
|---|---|
| 1 | task_id |
| 2 | project_id |
| 3 | name |
| 4 | description |
| 5 | priority |
| 6 | status |
| 7 | start_date |
| 8 | end_date |
| 9 | created_by |

Same as `taskDBS.csv` but **without the `unique_id` column** (9 fields instead of 10). Filename is derived by taking the project's `name` field and lowercasing it with `strlwr()` (e.g. project name `My Project` → file `Projects\my project.csv`); the file is deleted and recreated whenever a project's name is not the search key involved in deletion (see 6.7).

- **Created by:** `create_project()` (empty file, immediately after the `projectsDBS.csv` row is appended).
- **Written by:** `create_task()` (append); `update_task()` and `delete_task()` (rewrite-all, derived by filtering the main `taskDBS.csv` — see Section 10.2 for the exact difference between how `update_task()` and `delete_task()` reconcile the two files); `update_cancelled_project_tasks()` (rewrite-all, cancels every row).
- **Read by:** `create_task()` (to compute the next `task_id`), `view_tasks_by_project()`, `project_progress_report()` (with a fallback to a category-named file — see 15.2), `update_cancelled_project_tasks()`.

### 6.7 Temporary files and the rewrite pattern

Every "modify a CSV" operation in this codebase (update, delete, status change) follows the same pattern, with no exceptions found in the source:

```text
open <original>.csv for read
open <TEMP name>.csv for write
for each row in <original>.csv:
    parse row
    if row matches the target → apply the change (or omit the row, for deletes)
    write row to <TEMP name>.csv
close both files
remove(<original>.csv)
rename(<TEMP name>.csv, <original>.csv)
```

The specific temp filenames used are `tmp_credentialDBS.csv`, `tmp_projectsDBS.csv`, and `tmp_task.csv` (the same `tmp_task.csv` name is reused for both the main task database's temp file and a per-project task file's temp file — they live in different directories so this does not collide). `sort_project.csv` and `sort_task.csv` are always fully overwritten (`FILE_MODE_WRITE`, no temp/rename step) since they are pure derived/cache files, never read back for merging.

### 6.8 Sorted/derived files

- **`sort_project.csv`** — written by `sort_projects()`. Same 9-field schema as `projectsDBS.csv`. Projects whose status is `Cancelled` or `Completed` are skipped entirely (not written). Remaining projects are sorted descending by priority (`High`=3, `Medium`=2, `Low`=1) via `qsort`/`compare_project_priority`.
- **`sort_task.csv`** — written by `sort_tasks()`. Same 10-field schema as `taskDBS.csv`. Tasks whose status is `Cancelled` or `Completed` are skipped. Remaining tasks are sorted descending by priority via `qsort`/`sort_by_priority`.
- Neither sorted file is ever read back by any other function in the supplied source — no UI screen displays `sort_project.csv` or `sort_task.csv`'s contents. Their only observable effect is that `sort_projects()`/`sort_tasks()` also run the status-synchronization logic (for `sort_projects()`) as a side effect of being called.

---

## 7. Authentication Module (`auth.c` / `auth.h`)

### 7.1 `int create_user()`

Draws `user_registration_screen()`, generates a user ID via `generate_user_id()`, then reads (in order): full name (no validation), email (looped with `validate_email()` until valid), phone (looped with `validate_phone()` until valid), username (looped with `validate_user_name()` until valid), password (via `input_password()`, masked with `*`), and the answer to the fixed prompt "What Is Your Favourite Food" (no validation). Sets `role = "Individual"`. Appends a row to `userDBS.csv` and a row to `credentialDBS.csv` (`login_status = "logout"`). Calls `create_directories(username)`. Shows `account_create_success_screen()`. Does **not** log the new user in or write to `log.csv`.

### 7.2 `int login()`

Reads username-or-email and a masked password, calls `password_verify()`. On `VALID`: calls `change_login_status("login")`, shows `login_success_screen()`, and calls `dashboard()` (the login flow does not return to `main_menu()` until the user eventually logs out, at which point `dashboard()` returns and `login()`'s own `return 0` unwinds back into `main_menu()`'s loop). On invalid credentials: shows `invalid_login_screen()` and returns without ever reaching `dashboard()`.

### 7.3 `int logout()`

Calls `change_login_status("logout")`, then opens `log.csv` in write mode purely to truncate it, closes it, and shows `logout_successful_screen()`.

### 7.4 `int change_password()`

Reads email, the security-question answer, and a new masked password. Scans `credentialDBS.csv` row by row; if a row's email **and** security-question answer both match the input, that row's password field is replaced with the new password (the scan continues to the end of the file regardless, since it is rewriting every row to the temp file). After the rewrite/rename: if no matching row was found, shows `change_password_failed_screen()` and calls `main_menu()`; if a match was found, shows `change_password_successful_screen()`. (Note: because the function always rewrites the whole database, a "failed" change-password attempt still performs a full read/temp-write/remove/rename cycle even though nothing changed.)

### 7.5 `int generate_user_id(char id[])`

Reads `userDBS.csv`, keeps only the last row's `id` (later rows overwrite the value read from earlier rows). If the file is empty, `id` is left as `FIRST_USER_ID_VALUE` (`"U1001"`). Otherwise: strips the leading letter, parses the remaining digits into an integer, increments by 1, and writes the digits back into the same fixed-width buffer (so the number of digits is preserved — e.g. `U1099` → `U1100`, but the algorithm does not grow the string if incrementing would need an extra digit within its allotted width).

### 7.6 `int change_login_status(char status[])`

Looks up the current user via `get_user_name()` (i.e. whichever username is in `log.csv`), then rewrites `credentialDBS.csv`, setting that user's `login_status` field to the passed-in `status` string (`"login"` or `"logout"`).

### 7.7 `int password_verify(char username_or_email[], char password[])`

Opens `log.csv` for writing (truncating it) up front. Scans `credentialDBS.csv`; a row matches if the input equals that row's `email` (with the input password equal to that row's password) **or** equals that row's `username` (with the same password check). On the first match, writes that row's username into `log.csv` and stops scanning; returns `VALID`. If no row matches by end of file, returns `INVALID` and `log.csv` is left empty.

### 7.8 `int input_password(char password[])`

Reads characters one at a time via `getch()` until `ENTER` (13). `BACKSPACE` (8) removes the last character (and erases it on screen with `"\b \b"`) if any have been typed. Every other character is stored and echoed to the screen as `*`.

### 7.9 `char *get_user_name()`

Reads every line of `log.csv` (the loop keeps re-assigning, so only the last line actually survives — in practice the file only ever has one line) and returns a `malloc`'d copy of the first comma-separated token of that line. Callers are responsible for `free()`-ing the returned pointer (all callers in this codebase do so).

### 7.10 `int validate_user_name(char username[])`

Scans `credentialDBS.csv`; returns `INVALID` if any row's `username` field equals the input, otherwise `VALID` (i.e. it enforces username uniqueness).

### 7.11 `int validate_email(char email[])`

Two checks: (a) the input string must contain an `@` character; (b) the input must not already exist as an `email` field in `credentialDBS.csv`. Both must hold for the result to be `VALID`. There is no other format validation (no domain check, no check for exactly one `@`, etc.).

### 7.12 `int validate_phone(char phone[])`

`VALID` only if the input is exactly `MAX_PHONE_LENGTH` (10) characters long and every character is an ASCII digit. The registration UI shows a `+880` prefix label next to the input field, but that prefix is **not** part of what's typed or stored — the stored value is the raw 10 digits.

### 7.13 `int create_directories(char username[])`

Creates `..\database\<username>` and `..\database\<username>\Projects` via `CreateDirectory`, then creates four empty files inside `..\database\<username>\`: `projectsDBS.csv`, `taskDBS.csv`, `sort_task.csv`, `sort_project.csv` (each opened in write mode and immediately closed).

---

## 8. Project Management Module (`project.c` / `project.h`)

### 8.1 `int create_project()`

Generates a project ID via `generate_project_id()`. Reads name, category, description (all unvalidated free text), then priority via `project_priority_dashboard()` (a selection screen, not free text). Sets `status = "Created"` (`DEFAULT_PROJECT_STATUS`). Reads and validates start date and end date in a loop each, using `validate_date()`. Sets `created_by` from `get_user_name()`. Appends the row to `projectsDBS.csv`, then creates the empty per-project task file `Projects\<lowercased name>.csv`.

### 8.2 `int update_project()`

Prompts for a project ID or name. Rewrites `projectsDBS.csv` row by row into a temp file; if a row's `id` or `name` matches the input, calls `update_project_dashboard()` on that in-memory record **before** writing it to the temp file (so the edited values are what gets persisted). If no row matched by end of scan, the temp file is discarded and `project_not_found()` is shown; otherwise the temp file replaces the original and `project_update_successful()` is shown.

`update_project_dashboard()` (UI function, `ui.c`) presents:

```text
[1] Project Name        → change_project_name()
[2] Category            → change_project_category()
[3] Description         → change_project_description()
[4] Priority            → project_priority_dashboard() (selection)
[5] Status              → project_status_dashboard() (selection)
[6] Start Date          → change_project_start_date() (validated)
[7] End Date            → extend_project_deadline() (validated)
[ESC] Back              → project_management_dashboard()
```

Only one field can be changed per pass through `update_project()` (the function does not loop back to the update menu after a single field edit).

### 8.3 `int delete_project()`

Prompts for a project ID or name. Scans `projectsDBS.csv`; on a match, deletes that project's per-project task file (`Projects\<lowercased name>.csv`) and **omits** the row from the rewritten `projectsDBS.csv` (does not copy it to the temp file). If the project file can't be removed, the operation aborts (closes both handles, deletes the partial temp file, shows the generic failure screen, and returns without touching the original database). If no project matched, `project_not_found()` is shown and `project_management_dashboard()` is re-entered. On success, after `projectsDBS.csv` is replaced, the function additionally rewrites `taskDBS.csv`, **dropping every task row whose `project_id` equals the deleted project's id** — i.e. deleting a project cascades to remove all of that project's tasks from the main task database. (The per-project task file was already deleted outright as a file, so its own tasks are gone with it; this second pass specifically cleans the *main* `taskDBS.csv`, which is a separate copy of the same information.)

### 8.4 `int view_projects()`

Reads every row of `projectsDBS.csv` and shows each one, one screen at a time, via `project_show_screen()`, advancing on any keypress (`get_input`). If the file has no rows, `project_not_found()` is shown once at the end.

### 8.5 `int search_by_project_id_or_name()` / `int search_project_by_status()` / `int search_project_by_priority()`

Each prompts for its key (free-text id-or-name, or a selection from `project_status_dashboard()`/`project_priority_dashboard()`), scans `projectsDBS.csv`, and shows every matching row via `project_show_screen()`. `search_by_project_id_or_name()` stops after the first match (`break`); the status/priority searches show *all* matches, one screen per match, advancing on keypress. Only `search_by_project_id_or_name()` explicitly shows `project_not_found()` when nothing matched — the status/priority searches do not report "not found" if zero rows match.

### 8.6 Field update helpers

`change_project_name()`, `change_project_category()`, `change_project_description()` each show a single-field input screen and copy the typed value into the passed-in buffer, unvalidated. `change_project_start_date()` and `extend_project_deadline()` do the same but loop until `validate_date()` accepts the input. `change_project_status()` and `change_project_priority()` are thin wrappers that just call the corresponding selection dashboard (`project_status_dashboard()` / `project_priority_dashboard()`).

### 8.7 `int generate_project_id(char id[])`

Same increment-the-numeric-suffix algorithm as `generate_user_id()` (Section 7.5), seeded from the last row's `id` in `projectsDBS.csv`, defaulting to `"P1001"` when the file is empty.

### 8.8 `int get_path(char path[])`

Builds `..\database\<current username>\` (with a trailing backslash) by calling `get_user_name()` and freeing the returned pointer. This is the single shared helper every per-user database path is built from, in every module.

### 8.9 `int compare_project_priority(const void *a, const void *b)`

`qsort` comparator: maps `"High"`→3, `"Medium"`→2, `"Low"`→1 (any other/unrecognized string maps to 0), and returns `priority_b - priority_a` (descending order).

### 8.10 `int sort_projects()`

First calls `update_cancelled_project_tasks()`, `update_created_project_status()`, and `update_project_status_by_tasks()` (in that order — see Section 11), **then** reads `projectsDBS.csv`, skips any row whose status is `Cancelled` or `Completed`, sorts the rest by priority, and writes the result to `sort_project.csv`.

---

## 9. Task Management Module (`task.c` / `task.h`)

### 9.1 `int unique_task_id_generator()`

Reads the main `taskDBS.csv`, keeps the last row's `unique_id` (parsed with `atoi`), and returns `unique_id + 1`. Returns the sentinel `INITIAL_UNIQUE_TASK_ID_VALUE` (`10001`) if the file is empty or fails to open.

### 9.2 `int generate_task_id(char id[], char path[])`

Same increment-the-numeric-suffix algorithm as `generate_user_id()`/`generate_project_id()`, but the file it reads is **whatever path is passed in** — in `create_task()` this is the *per-project* task file, not the main `taskDBS.csv`. Defaults to `"T1001"` (`INITIAL_TASK_ID_VALUE`) if that file is empty. See Section 12.4 for why this makes `task_id` project-scoped rather than globally unique.

### 9.3 `int create_task()`

Prompts for a project ID or name; scans `projectsDBS.csv` for a match (comparing only `id` and `name`, the only two fields it parses). If not found, shows `project_not_found()`. If found, computes the per-project task file path, generates `unique_id` via `unique_task_id_generator()` (scoped to the main task database) and `task_id` via `generate_task_id()` (scoped to the per-project file). Reads name and description (free text), priority via `task_priority_dashboard()`, sets `status = "Created"`, and reads/validates start and end dates. Appends the full 10-field row to the main `taskDBS.csv`, and appends the 9-field row (no `unique_id`) to the per-project task file — writing to the per-project file is guarded by a null check (`if (project_task_open != NULL)`), so if that file can't be opened, the task is still recorded in the main database but silently not recorded per-project.

### 9.4 `int update_task()`

Prompts for a project ID or name, then a task ID or name. First rewrites the **main** `taskDBS.csv`: a row is a match if (`task_id` or `name` equals the input) **and** `project_id` equals the found project's id; on match, `task_update_dashboard()` is invoked on the in-memory record before it's written to the temp file. If no task matched, the temp file is discarded and `task_not_found()` is shown. If a match was found and the main database was successfully replaced, the function then **fully regenerates** the per-project task file by re-reading the (already updated) main `taskDBS.csv`, filtering to rows whose `project_id` matches, and writing those 9-field rows to a fresh per-project temp file, which replaces the original per-project file. (I.e., for updates, the per-project file is derived from the main database, not edited independently.)

`task_update_dashboard()` (UI function) presents:

```text
[1] Task Name              → change_task_name()
[2] Description            → change_task_description()
[3] Priority               → change_task_priority() → task_priority_dashboard() (selection)
[4] Status                 → change_task_status() → task_status_dashboard() (selection)
[5] Start Date             → change_task_start_date() (validated)
[6] End Date               → extend_task_deadline() (validated)
[7] Back                   → no case in the switch — see Sec. 19.4
[ESC] Back                 → task_management_dashboard()
```

### 9.5 `int delete_task()`

Prompts for a project ID or name, then a task ID or name. Unlike `update_task()`, this function updates the **per-project file first**: it scans the per-project task file, omitting the matching row (match = `task_id` or `name` equals input, **and** `project_id` equals the found project's id) from the rewritten file. If nothing matched, the operation aborts with `task_not_found()`. If a match was found, the function then **independently** re-scans the main `taskDBS.csv` with the same match criteria and omits the matching row there too (it does not derive this pass from the per-project file the way `update_task()` derives its per-project rewrite from the main database — both files are filtered directly from their own prior contents using the same search key).

### 9.6 `int view_tasks()`

Reads every row of the main `taskDBS.csv` and shows each one via `task_details_screen()`, advancing on keypress.

### 9.7 `int search_by_task_id_or_name()` / `int search_task_by_status()` / `int search_task_by_priority()`

Scan the main `taskDBS.csv`. `search_by_task_id_or_name()` matches on `task_id` or `name`, shows the first match, and stops (`break`); reports `task_not_found()` if nothing matched. `search_task_by_status()` and `search_task_by_priority()` (prompted via `task_status_dashboard()` / `task_priority_dashboard()` selection screens) show *every* matching row, one per screen, advancing on keypress; both report `task_not_found()` if zero rows matched by the end of the scan.

### 9.8 `int view_tasks_by_project()`

Prompts for a project ID or name; on a match, opens that project's per-project task file directly (not the main database) and shows every row in it via `task_details_screen_for_separate_project()`.

### 9.9 `int sort_tasks()`

Reads the main `taskDBS.csv` into an in-memory array (capped at `TASK_ARRAY_SIZE` = 1000 rows — additional rows beyond that are silently not read), skips rows with status `Cancelled` or `Completed`, sorts the rest descending by priority (`sort_by_priority`, same 3/2/1 mapping as the project comparator), and writes the result to `sort_task.csv`. Unlike `sort_projects()`, `sort_tasks()` does **not** trigger any status-synchronization function.

---

## 10. Project–Task Relationship

### 10.1 Two databases, one logical dataset

Every task exists in two places at once: the main, per-user `taskDBS.csv` (all of that user's tasks across all projects, with a global `unique_id`) and a per-project file under `Projects\` (only that project's tasks, no `unique_id`). Almost every task-mutating operation therefore has to touch both files; see Sections 9.3–9.5 for exactly how each operation keeps them in sync (and note that `update_task()` and `delete_task()` use different reconciliation strategies — one derives the per-project file from the main file, the other updates both independently from the same search key).

### 10.2 ID scoping

- `unique_id` — generated from the main `taskDBS.csv`; monotonically increasing per user, across all of that user's projects.
- `task_id` — generated from the **per-project** task file; monotonically increasing only within that one project. Two different projects belonging to the same user can therefore both contain a task with `task_id = "T1001"`.

### 10.3 Deleting a project cascades to its tasks

`delete_project()` removes the per-project task file outright and also strips matching rows from the main `taskDBS.csv` (Section 8.3). There is no soft-delete for projects or tasks — deleted rows are physically removed, not flagged. `DELETED_PROJECT_STATUS` (`"Deleted"`) and `DELETED_TASK_STATUS` (`"Deleted"`) are defined in the headers but are never assigned to any record anywhere in the source (see Section 19.6).

---

## 11. Automatic Status Synchronization

`sort_projects()` (Section 8.10) runs three synchronization passes, in this fixed order, every time it is called:

### 11.1 `int update_cancelled_project_tasks()`

For every project whose status is `Cancelled`: reads that project's per-project task file and rewrites every row's status to `Cancelled` (unconditionally — even if a task was already `Completed`); then does the equivalent pass over the main `taskDBS.csv`, setting `status = "Cancelled"` for every row whose `project_id` matches that cancelled project. This repeats for every cancelled project found in `projectsDBS.csv` on that pass (the main `taskDBS.csv` is fully re-read and re-written once per cancelled project, not once total).

### 11.2 `int update_created_project_status()`

For every project whose status is currently `"Created"` (`DEFAULT_PROJECT_STATUS`): scans the main `taskDBS.csv` for any task belonging to that project. If at least one exists, the project's status is changed to `"In Progress"` (`IN_PROGRESS_PROJECT_STATUS`). Projects not currently in `"Created"` status are left untouched by this function (so a project already `In Progress`, `Completed`, or `Cancelled` is not revisited here).

### 11.3 `int update_project_status_by_tasks()`

For every project (regardless of current status), counts its total tasks and its `Completed` tasks in the main `taskDBS.csv`. If the project has at least one task and every one of its tasks is `Completed`, the project's status is set to `"Completed"` (`COMPLETED_PROJECT_STATUS`). No other transition is made by this function.

### 11.4 When synchronization actually runs

Because these three functions are only invoked from inside `sort_projects()`, and `sort_projects()` is only called from `dashboard()` (once, at login) and from the top of `project_management_dashboard()`'s loop (on every redraw of that specific menu), status changes triggered by task edits are **not** guaranteed to be visible immediately after editing a task from the Task Management menu — they become visible the next time the user (re)enters Project Management, or the next time they log in.

---

## 12. ID Generation

`generate_user_id()`, `generate_project_id()`, and `generate_task_id()` all share the same approach:

1. Seed the output buffer with a fixed sentinel value (`U1001`, `P1001`, or `T1001`).
2. Read the target CSV file and keep only the **last** row's id column (earlier rows are overwritten in the loop, so only the final row's id is used as the seed).
3. If the file was empty, return the sentinel as-is.
4. Otherwise, strip the leading letter, parse the remaining digits into an integer, add 1, and write the digits back into the same character positions of the id string (so the total string length/format is preserved).

Because step 2 only looks at the very last row, ids are **not** derived from "the highest id present" in any general sense — they are derived from whichever row physically comes last in the file at read time (which, given the codebase always appends new rows and rewrites files in original row order during updates, in practice corresponds to the most recently created record, but this is a consequence of the file always being append-ordered, not something the ID generator itself guarantees).

---

## 13. Sorting

- **Projects:** `sort_projects()` / `compare_project_priority()` — descending by priority (`High` > `Medium` > `Low`), `Cancelled` and `Completed` projects excluded from the output entirely. Runs the three status-sync passes first (Section 11).
- **Tasks:** `sort_tasks()` / `sort_by_priority()` — same priority ordering and exclusion rule, applied to the main `taskDBS.csv`. Does not run any status-sync pass.
- Both comparators treat any priority string other than the literal `"High"`/`"Medium"`/`"Low"` as priority value `0` (lowest).
- Neither sort is stable in a documented sense; `qsort` does not guarantee original relative order is preserved among equal-priority items.

---

## 14. Searching

| Function | Scope | Match key | Behavior on no match |
|---|---|---|---|
| `search_by_project_id_or_name()` | `projectsDBS.csv` | id **or** name (exact) | `project_not_found()` |
| `search_project_by_status()` | `projectsDBS.csv` | status, chosen from a fixed 4-option list | (no explicit "not found" message) |
| `search_project_by_priority()` | `projectsDBS.csv` | priority, chosen from a fixed 3-option list | (no explicit "not found" message) |
| `search_by_task_id_or_name()` | main `taskDBS.csv` | task_id **or** name (exact) | `task_not_found()` |
| `search_task_by_status()` | main `taskDBS.csv` | status, chosen from a fixed 4-option list | `task_not_found()` |
| `search_task_by_priority()` | main `taskDBS.csv` | priority, chosen from a fixed 3-option list | `task_not_found()` |
| `view_tasks_by_project()` | per-project task file | project id or name to locate the file; then shows all rows in it | `task_not_found()` if the file has zero rows |

All matches are done with `strcmp` (case-sensitive, exact match) — there is no partial/substring search anywhere in the source.

---

## 15. Reporting Module (`report.c` / `report.h`)

All eight reports read directly from the per-user CSV files (they do not use the sorted derivative files). Each report screen is drawn once per matching record (or once total, for the two summary reports) and advances on `get_input`.

### 15.1 `int project_summary_report()`

Counts `total_projects`, and how many are in each of `Created` / `In Progress` / `Completed` / `Cancelled`, across all of `projectsDBS.csv`. Displays the five counters on one screen. **Uses the swapped `name`/`category` field order described in Section 19.1** — this has no visible effect on the summary counters themselves (they're keyed off the status field, which is parsed correctly), but the struct's `name`/`category` fields are mislabeled internally for the duration of this function.

### 15.2 `int project_progress_report()`

For every project, opens its per-project task file by lowercased project name; **if that file can't be opened, falls back to trying a file named after the lowercased category instead** (`Projects\<lowercased category>.csv`) before giving up. Counts total and completed tasks in whichever file opened successfully, computes `progress = completed / total * 100` (0 if there are no tasks), and shows one screen per project with id, name, task counts, and progress percentage.

### 15.3 `int overdue_projects_report()`

Shows every project whose `end_date` is earlier than today's date (plain string comparison, works correctly only because dates are stored as zero-padded `YYYY-MM-DD`) and whose status is neither `Completed` nor `Cancelled`. **Uses the swapped field order** (Section 19.1) — the "Project Name" shown on screen is actually the project's category value.

### 15.4 `int high_priority_projects_report()`

Shows every project with `priority == "High"` whose status is neither `Completed` nor `Cancelled`. **Also uses the swapped field order.**

### 15.5 `int task_summary_report()`

Counts `total_tasks` and tasks in each of six buckets: `Created` (labeled "Pending Tasks" on screen), a literal `"Planning"` status, a literal `"In_Progress"` status (underscore, distinct from the project status string `"In Progress"`), `Completed`, and `Cancelled`. Because no code path anywhere in the system ever assigns a task the status `"Planning"` or `"In_Progress"` (the only statuses ever written are `Created`, `In Progress`, `Completed`, `Cancelled` — see `task_status_dashboard()`), the "Planning Tasks" and "In Progress Tasks" counters on this report will always read `0` in normal use.

### 15.6 `int overdue_tasks_report()`

Shows every task whose `end_date` is before today and whose status is neither `Completed` nor `Cancelled`.

### 15.7 `int high_priority_tasks_report()`

Shows every task with `priority == "High"` whose status is neither `Completed` nor `Cancelled`.

### 15.8 `int pending_active_tasks_report()`

Shows every task whose status is neither `Completed` nor `Cancelled` (i.e., everything not finished or dropped — in practice this is `Created` or `In Progress` tasks).

---

## 16. Utility Module (`utility.c` / `utility.h`)

- **`pause_screen(int sec)`** — `Sleep(sec)` (Windows sleep, milliseconds despite the parameter name; call sites pass values like `1000`/`2000`, i.e. 1–2 seconds).
- **`clear_screen()`** — `system("cls")`.
- **`validate_date(char date[])`** — requires exactly 10 characters in `YYYY-MM-DD` format (dashes at positions 4 and 7, digits elsewhere), a month 1–12, and a day within that month's actual length (including real leap-year handling for February). Does not check the year is within any particular range, nor that the date is not in the past.
- **`current_time()`** — prints `HH:MM:SS` (space-padded, not zero-padded) directly to stdout at the current cursor position; returns nothing usable, it's a side-effecting print.
- **`current_date(char date[])`** — writes today's date as `YYYY-MM-DD` into the given buffer via `strftime`.
- **`is_overdue(char date[])`** — returns 1 if the given date string is lexicographically less than today's date string, else 0. Not called from anywhere else in the supplied source except indirectly duplicated logic inline in the report functions (the reports do their own `strcmp` against `current_date()` rather than calling `is_overdue()`).
- **`init_console()`** — sets console input/output code page to UTF‑8 on Windows (`#ifdef _WIN32` guarded; a no-op on other platforms, though the rest of the codebase would not compile there regardless).
- **`move_cursor(x, y)`** — `SetConsoleCursorPosition` to the given column/row.
- **`get_console_width()` / `get_console_height()`** — derived from `GetConsoleScreenBufferInfo`'s `srWindow` rectangle.
- **`live_clock(void *arg)`** — an infinite loop (`while(1)`) that writes the current `HH:MM:SS` directly into the console buffer at a fixed offset (`x+89, y+1`) once per second via `WriteConsoleOutputCharacterA`, then `Sleep(1000)`. Runs on its own thread — see Section 19.5 for how it's spawned.
- **`view_profile()`** — reads the current username from `log.csv`, looks up that username's `id` in `credentialDBS.csv`, then looks up that `id`'s full record in `userDBS.csv`. Displays id, username, name, email, phone (prefixed with `+880` at display time only), and role on `profile_screen()`. Waits for **any** keypress (not specifically `ESC`, despite the screen's `[ESC] Back` label — see Section 19.8), then unconditionally calls `dashboard()`.
- A large block of `validate_input()` at the bottom of `utility.c` is commented out in its entirety and is not compiled or called anywhere; it is dead/inactive code, not a working feature.

---

## 17. User Interface Module (`ui.c` / `ui.h`)

All screen-drawing and menu-loop code for every module lives in `ui.c` (not split across `auth.c`/`project.c`/`task.c`/`report.c`), organized under comment banners (`// auth.c UI START` … `// auth.c UI END`, etc.). `ui.h` declares every screen function plus the shared `enum error_type` and the `get_input` (`_getch()`) / `ESC` (27) macros.

### 17.1 `header_screen()`

Clears the screen, checks whether `log.csv` is non-empty (only to pick which footer function to call), draws the ASCII-art "PM S" logo banner and title, then calls `date_time_before_login(x, y+13)` **every single time it runs** (see Section 19.5 for the consequence of this). Note: despite its name and the fact that it checks `log.csv`, `header_screen()` always calls `date_time_before_login()`, never `date_time_after_login()` — `date_time_after_login()` is declared in `ui.h` but has no implementation anywhere in the source and is never called (Section 19.9).

### 17.2 Navigation pattern

Two different back-navigation styles are used throughout `ui.c`, inconsistently:

1. **Loop-local return** — a sub-menu function (e.g. `project_management_dashboard()`, `task_management_dashboard()`, `report_dashboard()`) runs its own `while(1)` loop and, on `ESC`, simply `return 0`s, letting whichever caller's loop (usually `dashboard()`) redraw next.
2. **Direct re-invocation** — a single-purpose dashboard (e.g. `update_project_dashboard()`, `task_update_dashboard()`, `project_status_dashboard()`, `project_priority_dashboard()`, `task_status_dashboard()`, `task_priority_dashboard()`) calls its parent menu function directly on `ESC` (e.g. `project_management_dashboard()` or `task_management_dashboard()`), growing the call stack by one frame rather than returning control up through the normal caller chain.

Both patterns are present in the shipped code; which one a given screen uses depends on that screen, not on any stated rule.

### 17.3 Input validation loops

Every menu waits for a keypress in a `do { choice = get_input; } while ((choice < <low> || choice > <high>) && choice != ESC);` loop — i.e. it blocks and re-reads until a key in the labeled numeric range or `ESC` is pressed. Because the range check is on the character comparison, keys are validated purely by ASCII range, not against how many options are actually wired up in the following `switch` (see Section 19.4 for the one place this allows a labeled option to silently do nothing).

### 17.4 Success / error / transitional screens

Every "successful"/"failed"/"not found" screen (`account_create_success_screen`, `project_created_successful`, `task_deleted_successful`, `invalid_login_screen`, `project_not_found`, `task_not_found`, etc.) follows the same pattern: clear screen → header → draw a single-line message box → `pause_screen(1000)` (1 second) → `redirecting_screen()` (which prints "REDIRECTING" with an animated ellipsis over four 0.5-second steps). None of these screens wait for a keypress; they are purely timed.

### 17.5 `something_went_wrong_screen(enum error_type error)`

Draws a single generic error box showing the message from `get_error_message()` (`"FILE OPEN ERROR"`, `"FILE CLOSE ERROR"`, `"SOMETHING FAILED"`, or `"UNKNOWN ERROR"`), waits 2 seconds (`pause_screen(2000)`), then calls `exit(1)` — see Section 18.

---

## 18. Error Handling

The only error-handling strategy in the codebase is: on any `fopen`/`fclose`/`remove`/`rename` failure, call `something_went_wrong_screen(...)`, which unconditionally terminates the entire process with `exit(1)` after a 2-second display. There is no retry logic and no graceful degradation. Because `something_went_wrong_screen()` never returns, code written after a `something_went_wrong_screen(FILE_OPEN_ERROR);` call inside an `if (... == NULL)` block (which is the overwhelming majority of file-open error checks in this codebase) is unreachable in practice, even though many of those call sites are not followed by an explicit `return` statement in the source.

---

## 19. Known Source-Level Inconsistencies

These are documented as observed, exactly as implemented, per the source-code-is-authority rule. None of these have been corrected in this document.

### 19.1 Swapped `name`/`category` field order in three report functions

`project_summary_report()`, `overdue_projects_report()`, and `high_priority_projects_report()` tokenize each `projectsDBS.csv` row as `id, category, name, description, priority, status, start_date, end_date, created_by` — i.e. the 2nd and 3rd CSV columns are assigned to `project.category` and `project.name` respectively (backwards). Every other project-reading function in the codebase (`create_project`, `update_project`, `delete_project`, `view_projects`, `search_by_project_id_or_name`, `search_project_by_status`, `search_project_by_priority`, `project_progress_report`, `update_cancelled_project_tasks`, `update_created_project_status`, `update_project_status_by_tasks`, `sort_projects`) uses the correct order `id, name, category, ...`. Net effect: the "Project Name" field shown on the Overdue Projects and High Priority Projects report screens actually displays that project's *category* value.

### 19.2 Dead status buckets in the task summary report

`task_summary_report()` counts tasks with the literal status strings `"Planning"` and `"In_Progress"` (underscore). No code path in the system ever writes those exact strings to a task's status field — `task_status_dashboard()`, the only place a task status is ever set, only offers `Created`, `In Progress` (space), `Completed`, `Cancelled`. Those two counters will always display `0`.

### 19.3 Unlabeled options in the Search menu

`search_dashboard()` prints options `[1]` and `[2]` with visible labels, and `[3]`/`[4]` with **no label text** (blank lines), but its `switch` still wires `'3'` → `search_project_by_status()` and `'4'` → `search_project_by_priority()` — those two options are fully functional but invisible to the user reading the menu.

### 19.4 Unhandled menu option in Update Task

`task_update_dashboard()`'s on-screen menu lists `[7] Back`, and its input-validation loop accepts keys `'1'`–`'7'`, but its `switch` statement has no `case '7'` (only `'1'`–`'6'` and `ESC` are handled). Pressing `7` passes validation and then falls through the switch doing nothing — the function simply returns. Only `ESC` (which does have a case, calling `task_management_dashboard()`) actually navigates back.

### 19.5 `header_screen()` respawns the live-clock thread on every screen

`header_screen()` — which is called on virtually every screen transition throughout the program — calls `date_time_before_login()`, which unconditionally calls `_beginthread(live_clock, 0, position)` every time it runs, with no tracking or cleanup of previously spawned threads. `live_clock()` itself never terminates (`while(1)` with no exit condition). In a normal session with many screen transitions, this spawns a correspondingly large number of concurrent background threads, all writing the time to the same fixed screen coordinate once per second.

### 19.6 `DELETED_PROJECT_STATUS` / `DELETED_TASK_STATUS` are defined but unused

Both `"Deleted"` status constants are defined in `project.h` and `task.h` respectively but are never assigned to any project or task record anywhere in the source. Deletion (`delete_project()`, `delete_task()`) physically removes the row from the relevant CSV file(s) rather than marking it with a deleted status.

### 19.7 Two inconsistent macros for the same "Projects" folder name

`auth.h` defines `PROJECTS_FOLDER` as `"Projects"` (no trailing separator; call sites append `"\\"` themselves). `project.h` separately defines `PROJECT_FOLDER_NAME` as `"Projects\\"` (i.e. already ending in one backslash). Functions that use `PROJECT_FOLDER_NAME` (e.g. `update_cancelled_project_tasks()`) then *also* concatenate an additional `"\\"` afterward, producing a doubled backslash in the resulting path (`...Projects\\\...`), whereas functions using `PROJECTS_FOLDER` (e.g. `create_project()`, `create_task()`, `delete_task()`, `view_tasks_by_project()`) produce a single backslash. Both forms are generally tolerated by the Windows path APIs used here, but the two macros and their usage are not consistent with each other.

### 19.8 `view_profile()`'s "[ESC] Back" is not actually ESC-gated

`profile_screen()` labels its exit option `[ESC] Back`, but `view_profile()` (in `utility.c`) waits for a single `get_input` of **any** key and then unconditionally calls `dashboard()` regardless of which key was pressed — there is no check that the key was specifically `ESC`.

### 19.9 `date_time_after_login()` is declared but never implemented or called

`ui.h` declares `int date_time_after_login(int x, int y);`. No function with that name is defined anywhere in `ui.c` (or any other `.c` file), and nothing calls it. `header_screen()` always calls `date_time_before_login()` regardless of login state.

### 19.10 Passwords and the security "question" are stored and compared as plain text

`credentialDBS.csv` stores the password field exactly as typed (no hashing, no encryption). The "security question" is a single hardcoded UI label — "What Is Your Favourite Food" — not a user-selectable question; only the typed answer is stored, and it is compared with plain `strcmp`.

---

## 20. Function Reference

### Authentication (`auth.h`)
```c
int create_user();
int login();
int logout();
int change_password();
int generate_user_id(char id[]);
int change_login_status(char status[]);
int password_verify(char username_or_email[], char password[]);
int input_password(char password[]);
char *get_user_name();
int validate_user_name(char username[]);
int validate_email(char email[]);
int validate_phone(char phone[]);
int create_directories(char username[]);
```

### Project Management (`project.h`)
```c
int create_project();
int view_projects();
int update_project();
int delete_project();
int change_project_name(char name[]);
int change_project_category(char category[]);
int change_project_description(char description[]);
int change_project_status(char status[], int x, int y);
int change_project_priority(char priority[], int x, int y);
int change_project_start_date(char start_date[]);
int extend_project_deadline(char deadline[]);
int generate_project_id(char id[]);
int sort_projects();
int search_by_project_id_or_name();
int search_project_by_status();
int search_project_by_priority();
int get_path(char path[]);
int create_project_screen(int x, int y);
int compare_project_priority(const void *a, const void *b);
int update_cancelled_project_tasks();
int update_created_project_status();
int update_project_status_by_tasks();
```

### Task Management (`task.h`)
```c
int unique_task_id_generator();
int generate_task_id(char id[], char path[]);
int create_task();
int view_tasks();
int update_task();
int delete_task();
int view_tasks_by_project();
int change_task_name(char name[]);
int change_task_description(char description[]);
int change_task_status(char status[]);
int change_task_priority(char priority[]);
int change_task_start_date(char start_date[]);
int extend_task_deadline(char deadline[]);
int search_by_task_id_or_name();
int search_task_by_status();
int search_task_by_priority();
int sort_tasks();
int sort_by_priority(const void *a, const void *b);
```

### Reporting (`report.h`)
```c
int project_summary_report();
int project_progress_report();
int overdue_projects_report();
int high_priority_projects_report();
int task_summary_report();
int overdue_tasks_report();
int high_priority_tasks_report();
int pending_active_tasks_report();
```

### Utility (`utility.h`)
```c
int pause_screen(int sec);
int clear_screen();
int validate_date(char date[]);
int current_time();
int current_date(char date[]);
int is_overdue(char date[]);
int init_console();
int move_cursor(int x, int y);
int get_console_width();
int get_console_height();
void live_clock(void *arg);
int view_profile();
```

---

## 21. UI Screen Reference (`ui.h`)

```c
// main menu / dashboard
int header_screen();
int main_menu();
int dashboard();

// auth screens
int user_registration_screen(int x, int y);
int account_create_success_screen(int x, int y);
int user_login_screen(int x, int y);
int login_success_screen(int x, int y);
int redirecting_screen(int x, int y);
int invalid_login_screen(int x, int y);
int change_password_successful_screen(int x, int y);
int change_password_failed_screen(int x, int y);
int logout_successful_screen(int x, int y);
int change_password_screen(int x, int y);

// project screens
int project_management_dashboard();
int create_project_screen(int x, int y);
int search_project_by_id_or_name_screen(int x, int y);
int update_project_dashboard(struct p_details *project, int x, int y, int priority_x, int priority_y);
int change_project_name_screen(int x, int y);
int change_project_category_screen(int x, int y);
int change_project_description_screen(int x, int y);
int change_project_start_date_screen(int x, int y);
int extend_project_deadline_screen(int x, int y);
int project_show_screen(int x, int y);
int project_status_dashboard(char status[], int x, int y);
int project_priority_dashboard(char priority[], int x, int y);
int project_created_successful(int x, int y);
int project_update_successful(int x, int y);
int project_deleted_successful(int x, int y);
int project_not_found(int x, int y);

// task screens
int task_management_dashboard();
int create_task_screen(int x, int y);
int search_task_by_id_or_name_screen(int x, int y);
int task_update_dashboard(struct t_details *task, int x, int y);
int change_task_name_screen(int x, int y);
int change_task_description_screen(int x, int y);
int change_task_start_date_screen(int x, int y);
int extend_task_deadline_screen(int x, int y);
int task_details_screen(int x, int y);
int task_details_screen_for_separate_project(int x, int y);
int task_status_dashboard(char status[], int x, int y);
int task_priority_dashboard(char priority[], int x, int y);
int task_created_successfully(int x, int y);
int task_not_found(int x, int y);
int task_deleted_successful(int x, int y);
int task_update_successful(int x, int y);

// report screens
int report_dashboard();
int project_summary_report_screen(int x, int y);
int project_progress_report_screen(int x, int y);
int overdue_projects_report_screen(int x, int y);
int high_priority_projects_report_screen(int x, int y);
int task_summary_report_screen(int x, int y);
int overdue_tasks_report_screen(int x, int y);
int high_priority_tasks_report_screen(int x, int y);
int pending_active_tasks_screen(int x, int y);

// other
int search_dashboard();
int profile_screen(int x, int y);
int something_went_wrong_screen(enum error_type error);
char *get_error_message(enum error_type error);
int date_time_before_login(int x, int y);
int date_time_after_login(int x, int y);   // declared only — never defined or called
```

---

## 22. Important Constants

```text
// auth.h
DATABASE_DIR                 = ..\database\
USER_DATABASE_FILE           = ..\database\userDBS.csv
CREDENTIAL_DATABASE_FILE     = ..\database\credentialDBS.csv
TEMP_CREDENTIAL_DATABASE_FILE= ..\database\tmp_credentialDBS.csv
LOG_FILE                     = ..\database\log.csv
PROJECTS_FOLDER               = Projects
PROJECT_DATABASE_FILE         = projectsDBS.csv
TASK_DATABASE_FILE            = taskDBS.csv
SORTED_TASK_FILE              = sort_task.csv
SORTED_PROJECT_FILE           = sort_project.csv
DEFAULT_ROLE_NAME             = Individual
LOGIN_STATUS_VALUE            = login
LOGOUT_STATUS_VALUE           = logout
FIRST_USER_ID_VALUE           = U1001
MAX_PHONE_LENGTH               = 10

// project.h
PROJECT_DATABASE_FILE          = projectsDBS.csv
TEMP_PROJECT_DATABASE_FILE     = tmp_projectsDBS.csv
SORTED_PROJECT_FILE            = sort_project.csv
PROJECT_FOLDER_NAME            = Projects\        (note trailing backslash — see 19.7)
PROJECT_FILE_EXTENSION         = .csv
DEFAULT_PROJECT_STATUS          = Created
DELETED_PROJECT_STATUS          = Deleted   (unused — see 19.6)
CANCELLED_PROJECT_STATUS        = Cancelled
COMPLETED_PROJECT_STATUS        = Completed
IN_PROGRESS_PROJECT_STATUS      = In Progress

// task.h
INITIAL_TASK_ID_VALUE            = T1001
INITIAL_UNIQUE_TASK_ID_VALUE     = 10001
TEMP_TASK_DATABASE_FILE          = tmp_task.csv
TASK_FILE_EXTENSION              = .csv
TASK_ARRAY_SIZE                  = 1000   (in-memory cap for sort_tasks())
DEFAULT_TASK_STATUS               = Created
DELETED_TASK_STATUS               = Deleted   (unused — see 19.6)
CANCELLED_TASK_STATUS             = Cancelled
COMPLETED_TASK_STATUS             = Completed

// ui.h
get_input  = _getch()
ESC        = 27

// auth.h (shared key codes)
ENTER      = 13
BACKSPACE  = 8
ESCAPE     = 27
```

---

## 23. Module Dependency Summary

```text
auth.h
└── ui.h

project.h
├── auth.h
├── task.h
├── utility.h
└── ui.h

task.h
├── ui.h
└── project.h

report.h
├── project.h
├── task.h
├── ui.h
└── utility.h

utility.h
├── auth.h
├── ui.h
└── project.h

ui.h
├── project.h
├── task.h
├── auth.h
├── report.h
└── utility.h
```

`project.h` and `task.h` include each other (`project.h` includes `task.h`, and `task.h` includes `project.h`); both rely on include guards (`#ifndef PROJECT_H` / `#ifndef TASK_H`) to avoid infinite recursion. `ui.h` sits at the top, pulled in by every other module, and itself pulls in every other module — the header graph is a single tightly-coupled cluster rather than a layered dependency chain.

---

## 24. Complete High-Level Data Flow

```text
                          MAIN MENU  (main_menu, ui.c)
                                │
              ┌─────────────────┼──────────────────┐
              │                 │                  │
          Register            Login          Forgot Password
       create_user()        login()         change_password()
          (auth.c)          (auth.c)            (auth.c)
              │                 │                  │
              └─────────────────┼──────────────────┘
                                ↓
                    DASHBOARD (dashboard, ui.c)
              sort_projects() + sort_tasks() once at entry
                                │
     ┌───────────┬──────────────┼──────────────┬───────────┐
     │           │              │              │           │
 Project      Task          Reports         Search      Profile
Management  Management    report.c        (project.c   view_profile()
project.c    task.c                        + task.c)    (utility.c)
     │           │              │              │
     └───────────┴──────┬───────┴──────────────┘
                         ↓
                     utility.c  (dates, console, files)
                         ↓
                       ui.c  (drawing, input, navigation)
                         ↓
             ..\database\...csv  (persistent storage)
```

---

## 25. Canonical Project Context

This document describes the supplied implementation exactly as written. When used as context for future work on this codebase, the source implementation is the authority for:

- Function names, parameters, and return types
- Structure names and field order
- Macro names and literal values
- Database file names, paths, and field order
- ID formats and generation algorithms
- Status and priority literal values
- UI menu options and navigation behavior
- File handling and the read/temp-write/remove/rename pattern
- Project/task synchronization behavior (including its timing/triggering, Section 11.4)
- Report behavior, including the field-order inconsistency in Section 19.1
- User directory/file creation behavior
