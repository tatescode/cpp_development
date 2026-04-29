# The C++ Pipeline

**A research-informed program to take a self-taught learner to professional programmer (security/systems track), C++ as the primary language.**

Designed in three iterative passes, ending in a final detailed pipeline. The student is assumed to be motivated, self-directed, and willing to spend ~6 hours/day in 90-minute focused blocks. Total runway: ~12–18 months.

---

## Part 1 — Pedagogical foundation (the research)

These are the load-bearing findings the pipeline is built on. Every stage below is shaped by them.

**1. Read code before you write code.** Lister, Fidge & Teague (2009) showed novices need ~50% accuracy on code-tracing tasks before they can independently write code. Most learners reverse this — they write before they can read, then plateau as broken mental models accumulate. The pipeline front-loads code reading aggressively.

**2. PRIMM cycle for new concepts** (Sentance, Waite & Kallia, 2019). Predict → Run → Investigate → Modify → Make. You meet a concept by predicting what existing code does, run it to check, investigate why your prediction was wrong, modify it in small ways, and only *then* write your own from scratch. This is the unit cycle for learning every new language feature.

**3. Worked examples for novices, faded to problem-solving for experts** (Sweller, cognitive load theory). Novices benefit massively from studying complete worked examples — problem-solving from scratch overloads working memory before schemas form. As skill grows, the *expertise reversal effect* kicks in: worked examples become a drag and you need real problems. The pipeline grades from worked examples → completion problems → Parsons problems → blank-page projects.

**4. Subgoal labeling** (Margulieux & Catrambone, 2016). Annotating chunks of code with their *purpose* ("validate input", "advance pointer to next token") rather than just their mechanics produces measurably better transfer. The student writes their own subgoal labels on every worked example.

**5. Direct instruction beats pure discovery for novices** (Kirschner, Sweller & Clark, 2006 — "Why Minimal Guidance During Instruction Does Not Work"). Project-based learning is powerful but only when scaffolded by explicit instruction of the underlying concepts. "Just build something" is a known failure pattern. Each project is preceded by direct instruction of the concepts it requires.

**6. The notional machine must be taught explicitly.** Misconceptions about how the machine actually executes code (memory layout, evaluation order, lifetime, indirection) are the single largest source of novice errors and the hardest to debug. The pipeline includes explicit instruction on the C++ memory and execution model — not as an afterthought, but as a foundation.

**7. Deliberate practice, not just practice** (Ericsson). Time-on-task is not the variable; *focused work just outside the comfort zone, with feedback, on specific weaknesses* is. Casual coding plateaus fast. The pipeline includes weakness-targeted drills, not just project work.

**8. Retrieval practice + spaced repetition.** Re-reading produces the illusion of mastery. Active retrieval at expanding intervals produces actual mastery. Each stage uses spaced retrieval (Anki-style) for syntax/idioms and *forced reuse* (later projects must use earlier projects' code) for higher-level concepts.

**9. Self-explanation.** Verbalizing what code does and why — out loud or in writing — produces measurable gains and surfaces broken mental models. Every project ends with a written self-explanation.

**10. Schemas, not snippets.** The expert/novice gap (Adelson 1984; Lister et al. 2007) is not knowing more syntax — it's having abstract *plans* (schemas) like "iterate-and-accumulate", "two-pointer scan", "RAII handle wrapper". The pipeline names these schemas explicitly and drills them.

**Synthesis:** Read before write. Direct instruction before project. Worked example → completion → blank. Drill the notional machine. Label subgoals. Force retrieval. Name schemas.

---

## Part 2 — Iteration 1 (rough cut)

A naïve linear curriculum:

1. Syntax & control flow (4 wks)
2. Functions & arrays (3 wks)
3. Pointers & memory (4 wks)
4. OOP (4 wks)
5. STL (3 wks)
6. Templates (3 wks)
7. Concurrency (3 wks)
8. Systems/Win32 (6 wks)
9. Portfolio projects (months 6–18)

**What's wrong:** This is a table of contents, not a pipeline. It says nothing about *how* to learn each stage. It treats "OOP" and "templates" as monoliths. It puts projects only at the end. It ignores cognitive load progression. It doesn't force retrieval. A student following this would learn syntax and stall.

---

## Part 3 — Iteration 2 (apply the research)

Restructure each stage as a unit with a fixed internal shape, and chain projects so later ones force earlier code to be reused.

**Per-stage structure:**
- Direct instruction on the concept + the relevant notional-machine model
- Code-reading drills (PRIMM Predict + Investigate)
- Worked examples with subgoal labels
- Completion problems (fill in the missing piece)
- Parsons problems (rearrange shuffled code)
- Blank-page exercises
- A small project that consumes the previous stage's deliverable
- Spaced retrieval cards added to deck
- Written self-explanation deliverable
- Explicit competency gate before next stage

**Project chain (rough):** CLI calculator → text parser → hex viewer → log parser → IOC extractor → mini detection engine → Win32 process enumerator → ETW consumer → PE parser → DLL injector → shellcode loader → published portfolio.

**What's still wrong:** The stages are still loosely defined. "OOP" is one stage but should be split — interfaces and inheritance are different cognitive jumps from value semantics. Concurrency is too late for code that touches the OS. The competency gates aren't operationalized. There's no plan for what to do when stuck. The drilling cadence isn't specified.

---

## Part 4 — Iteration 3 (the final pipeline)

Twelve stages. Each stage names its concepts, its notional-machine focus, its drills, its project, its competency gate, and its expected duration. Times assume ~6 hours/day, 5 days/week (security learners often work weekends; build in slack). The pipeline is sequenced so that *every project reuses code from at least one earlier project* — this forces real retrieval and refactoring, the way professional codebases actually grow.

A glossary of recurring terms:

- **Worked example study:** read complete code, predict line-by-line behavior, write subgoal labels in the margin, run, compare prediction to reality.
- **Completion problem:** code with strategic blanks; fill them.
- **Parsons problem:** correctly-written code shuffled; reorder it. Use [parsons.problemsolving.io](https://parsons.problemsolving.io) or hand-rolled.
- **Blank-page exercise:** small spec, no scaffolding, write from scratch.
- **Anki cards:** flashcards added at end of each stage. Format: front = concept/idiom, back = minimal code example. Review daily, ~10 minutes.
- **Self-explanation doc:** 300–600 words at end of each project, written in your own words, answering: what does this do, what schema does it instantiate, where could it fail, what would I change.
- **Competency gate:** specific, falsifiable check. If you fail, you go back, not forward.

---

### STAGE 0 — Environment, toolchain, and the loop (3 days)

Before any C++ proper. Most beginner attrition happens here.

**Concepts:** compiler vs interpreter, translation units, the build/run/debug loop, what an editor does vs what a compiler does, what a debugger is.

**Tooling installed and verified:** g++ and clang++ on Linux/WSL, MSVC on Windows, CMake, Git, a real debugger (gdb or the VS debugger), an LSP-capable editor (VS Code with clangd, or CLion).

**Drill:** Compile and run "hello world" five different ways — `g++ main.cpp`, with explicit `-std=c++20 -Wall -Wextra -Wpedantic`, via CMake, via `clang++` with `-fsanitize=address,undefined`, and inside the debugger with a breakpoint on `main`. Step through each one and watch the program counter move.

**Notional-machine focus:** what happens between "save file" and "see output". Compilation as a real, observable process — not magic.

**Gate:** can build and step through a multi-file project from the command line without an IDE; can read a compiler error and locate the offending line.

---

### STAGE 1 — The grammar of expressions (1.5 weeks)

**Concepts:** primitive types, integer promotion, operator precedence, control flow (`if`/`else`/`switch`/`while`/`for`), I/O via `<iostream>`, basic functions, scope.

**Notional machine:** the stack frame. Variables as named storage on the stack. Function call/return as stack push/pop. Draw it on paper for every function in every exercise. This drawing habit pays dividends through stage 12.

**Mode:** mostly worked-example study. ~70% of time reading and predicting, ~30% writing. This will feel slow. It is correct.

**Reading drill:** trace 30+ programs from learncpp.com chapters 1–8 by hand on paper before running. Predict every variable's value at every line.

**Project:** *Calculator REPL*. Reads `+ - * /` expressions one per line, prints result, exits on `quit`. Must handle malformed input without crashing.

**Anki cards added:** ~40. (`for` loop syntax, `switch` fallthrough, integer overflow behavior, `cin` failure modes, etc.)

**Gate:** given any 20-line program from learncpp ch. 1–8, predict output with ≥80% accuracy on first read. This is the Lister threshold. Do not skip it.

---

### STAGE 2 — Functions, arrays, strings, and the standard library starter set (2 weeks)

**Concepts:** pass-by-value vs pass-by-reference, `const` correctness, `std::string`, `std::vector`, `std::array`, range-based `for`, function overloading, default arguments.

**Notional machine:** what does pass-by-reference *actually do*? Draw two stack frames sharing a memory cell. What does `const T&` mean at the machine level? Why is `std::string s = other_string` potentially expensive?

**Schemas to name and drill:** *iterate-and-accumulate*, *iterate-and-filter*, *find-first*, *swap*, *count-occurrences*. These are the universal small patterns. You should be able to write each one blank-page in under 60 seconds by the end of this stage.

**Mode:** worked example → completion → Parsons → blank, in that order, for each new concept.

**Project:** *Text file parser v1*. Reads a file, splits into lines, splits lines into tokens, prints word frequency sorted descending. No pointers yet — `std::string` and `std::vector<std::string>` only.

**Reuse from prior stage:** none yet, but the calculator REPL gets refactored to take expressions from a file as a 30-minute warmup.

**Self-explanation doc** for the parser project.

**Anki cards added:** ~60.

**Gate:** implement, blank-page, in 30 minutes: a function that takes a `std::vector<int>`, returns a new vector containing only elements occurring more than once, in original order. Compiles clean with `-Wall -Wextra -Wpedantic`. No memory bugs under ASan.

---

### STAGE 3 — The notional machine, deeply: pointers, references, memory layout (3 weeks)

This is the single most important stage. Most C++ learners are weak here forever because they speedrun it. You will not.

**Concepts:** address-of and dereference, raw pointers, `nullptr`, references, arrays decaying to pointers, pointer arithmetic, stack vs heap, `new`/`delete`, dangling pointers, double-free, use-after-free, buffer overflows, the C-string convention.

**Notional machine:** the *full* memory model. Stack growing down, heap growing up, code segment, data segment, BSS. Draw a diagram for every nontrivial program you write this stage. When you write `int* p = new int(42);`, draw the box on the heap, the box on the stack holding the address, and the arrow.

**Tooling added:** AddressSanitizer (`-fsanitize=address,undefined`), Valgrind, gdb's `print`, `x/`, `info locals`, `bt`. Run every program through ASan from now on. Forever.

**Mode:** for the first week, exclusively reading and tracing. No writing. Read other people's pointer code and predict the memory state at each line. This will feel wrong. Do it anyway — the research is unambiguous.

**Drills (deliberate practice, weakness-targeted):**
- Implement `strlen`, `strcpy`, `strcmp`, `memcpy`, `memmove` from scratch using only raw pointers. Each must pass a property-based test.
- Write a function that reverses an array in place using two pointers.
- Write a linked list with `new`/`delete`. Use it. Then use ASan to break it on purpose (introduce a use-after-free, a leak, a double-free) and watch what ASan says. *Knowing the symptom of each bug class is a skill.*

**Project:** *Hex viewer*. CLI tool: `hexview <filename>` prints the file as offset / hex bytes / ASCII gutter, like `xxd`. Must handle binary files, large files (read in chunks), and bad input. Uses raw pointers and manual buffer management deliberately — you'll rewrite it in stage 5.

**Reuse from prior stage:** the text parser's tokenizer is refactored to operate on a `const char*` buffer instead of `std::string`. Same behavior, lower-level implementation.

**Self-explanation doc** specifically explaining the memory layout of the hex viewer at runtime.

**Anki cards added:** ~50, including ASan/Valgrind error messages with their meanings.

**Gate:** given a small program with a deliberately-planted memory bug (one of: leak, UAF, double-free, OOB read, OOB write, uninitialized read), identify which bug it is from the ASan output alone, then fix it. Do this for 10 different programs back-to-back. <5 minutes per program.

This gate is the single most important one in the pipeline for the security/systems track. If you can't pass it, *you go back to the start of stage 3*. Do not negotiate.

---

### STAGE 4 — Structs, classes, and the object lifecycle (2 weeks)

**Concepts:** `struct` vs `class`, member functions, `this`, constructors, destructors, the *rule of three* (then five), copy semantics, deliberately-broken classes that leak.

**Notional machine:** what does the compiler *actually generate* when you write a class? `cppinsights.io` is your friend — paste your code, see what the compiler sees. Look at the implicit copy constructor. Understand why it's wrong for a class that owns a raw pointer.

**Schemas:** *resource handle*, *value type*, *named-constructor idiom*.

**Mode:** worked examples first. Read 20+ class implementations from real codebases (start with the EASTL or Boost source — pick something small) before writing your own.

**Drill:** write a `String` class from scratch that owns its buffer. Implement constructor, destructor, copy constructor, copy assignment. Make every operation crash safely (no UB) under ASan. Then deliberately introduce the rule-of-three violation, run it, watch it crash. Fix it. Now you understand the rule of three not as a rule but as a *consequence*.

**Project:** *Hex viewer v2*. Same external behavior, but now built around a `FileBuffer` class that owns its memory. Add a `--diff <other_file>` flag that highlights byte differences between two files.

**Reuse:** stage 3's hex viewer becomes the starting commit; you refactor toward classes.

**Anki cards added:** ~40.

**Gate:** explain in writing, without notes, what each of the rule-of-three (and rule-of-five) members does, when the compiler generates each, and what the implicit version does for a class containing a raw pointer. Then explain why this whole problem disappears in stage 5.

---

### STAGE 5 — RAII, smart pointers, and modern resource management (1.5 weeks)

**Concepts:** RAII as the central idiom of C++, `std::unique_ptr`, `std::shared_ptr`, `std::make_unique`, ownership semantics, when smart pointers are the *wrong* choice (which is more often than tutorials suggest).

**Notional machine:** what does a `unique_ptr` look like in memory? (Answer: it's a raw pointer with a destructor.) What does `shared_ptr` look like? (Answer: two pointers — one to the object, one to a control block with a refcount.) Draw both.

**Mode:** PRIMM-heavy. Lots of reading and predicting. Smart-pointer code looks deceptively simple; the cognitive load is in the ownership semantics, which are invisible.

**Drill:** rewrite stage 3's linked list using `unique_ptr`. Notice that `next` should be `unique_ptr<Node>`, but `prev` (in a doubly-linked list) cannot be — it must be a raw observing pointer. *Articulate why.* This is the single most important conversation about ownership you will have.

**Project:** *Hex viewer v3*. Refactor `FileBuffer` to use `unique_ptr<unsigned char[]>` instead of raw `new[]`/`delete[]`. Compare line counts and bug surface to v2. Notice that the destructor disappears.

**Anki cards added:** ~25.

**Gate:** given five small programs, identify which use of smart pointers is correct, which is unnecessary (a stack value would do), which is a memory leak (cyclic `shared_ptr`), and which is a use-after-free (`unique_ptr` aliased to a raw pointer that outlives it).

---

### STAGE 6 — STL: containers, iterators, algorithms (2 weeks)

**Concepts:** `vector`, `array`, `string`, `string_view`, `unordered_map`, `map`, `set`, `deque`, `list`, `optional`, `variant`, iterator categories, `<algorithm>`, lambdas, `std::function`, ranges (C++20) as a peek ahead.

**Notional machine:** iterators as generalized pointers. `unordered_map` as a hash table — what's a load factor? What's a collision? `map` as a tree — what's the cost of `lower_bound`?

**Schema:** *iterate-and-accumulate* now generalizes to `std::accumulate`. *Iterate-and-filter* generalizes to `std::copy_if`. Recognize that you've already been writing these by hand for months — now you have the standard names.

**Drill:** for each of `transform`, `accumulate`, `copy_if`, `partition`, `find_if`, `any_of`, `all_of`, `sort` with custom comparator, `lower_bound`, `unique`: write three uses in three different domains. Burn the muscle memory.

**Project:** *IOC extractor*. CLI tool that reads logs / arbitrary text and extracts IPs, domains, hashes (MD5/SHA1/SHA256), URLs, email addresses. Output as JSON. Use `<regex>`, `unordered_set` for dedup, `std::optional` for parse results. Must handle multi-GB files via streamed reading.

**Reuse:** the text parser from stage 2 is the starting point. The hex viewer's `FileBuffer` is reused for the streaming reader.

**Self-explanation doc** specifically describing how each STL component you used was the right (or wrong) choice and what the alternatives were.

**Anki cards added:** ~80, mostly STL idioms. This deck pays for itself for the rest of your career.

**Gate:** given a list of 20 small algorithmic tasks ("dedup preserving order", "find max by key", "group by predicate"), name the correct STL algorithm or chain of algorithms for each. <2 minutes per task. No reference material.

---

### STAGE 7 — OOP, inheritance, polymorphism, and design (2 weeks)

**Concepts:** virtual functions, abstract base classes, the vtable, dynamic dispatch, multiple inheritance (and why to avoid it), composition vs inheritance, interfaces, `final` and `override`, the open/closed principle, dependency inversion. Light touch on design patterns — strategy, factory, observer — *because they show up in real code*, not because they're inherently good.

**Notional machine:** the vtable. Draw it. For a class with virtual methods, draw the object's hidden vtable pointer, draw the vtable itself, draw the function pointers in it. Understand that virtual dispatch costs an indirection. Understand why `final` lets the compiler devirtualize.

**Mode:** read first. Find a small open-source C++ project that uses inheritance well (e.g., a small game engine or a parser library) and trace a polymorphic call from a base interface to the concrete implementation. Do this five times before writing your own polymorphic class.

**Drill:** implement a `Shape` hierarchy three different ways — first with inheritance, then with `std::variant` and `std::visit`, then with type erasure (a `Drawable` concept). Compare. Notice that inheritance is one option, not *the* option.

**Project:** *Mini detection engine*. A program that loads a directory of detection rules (start with a tiny YAML-ish format you define; you'll align it with Sigma in stage 12) and applies them to a stream of log events. Each rule type is a class implementing a `Rule` interface. New rule types added by subclassing. This is a Sigma proto-engine.

**Reuse:** the IOC extractor from stage 6 becomes one of the rule types.

**Anki cards added:** ~30.

**Gate:** explain in writing when you would use inheritance, when you would use `std::variant`, and when you would use templates (foreshadowing stage 8). Give a concrete example where each is the right choice and the others are wrong.

---

### STAGE 8 — Templates and generic programming (2 weeks)

**Concepts:** function templates, class templates, template deduction, SFINAE (briefly, with apologies), `concepts` (C++20 — use these, not SFINAE, where possible), variadic templates, `constexpr`. Template error messages.

**Notional machine:** templates as compile-time code generation. The compiler stamps out one copy of your template per type used. Look at the generated code in `cppinsights.io`. Understand why templates blow up binary size and compile time.

**Mode:** worked example heavy. Templates have terrible error messages and you will be doing PRIMM-style prediction on them for a long time.

**Drill:** write generic versions of the stage 2 schemas (*find-first*, *count-if*, *swap*) as function templates. Then write a small `Vector<T>` class template. Then write `Vector<T, Allocator>`. Each step makes the previous look obvious.

**Project:** *Generic event pipeline*. Refactor the mini detection engine so that the event stream is a templated `Pipeline<Event>` with stages that can be composed. A logging stage, a filter stage, a rule-application stage, an output stage. Each stage takes the previous's output as input. This is a real architecture you'll use repeatedly in security tooling.

**Reuse:** mini detection engine from stage 7.

**Anki cards added:** ~40.

**Gate:** given a feature request ("add support for events with a `priority` field that not all event types have"), implement it correctly using templates and concepts. The non-priority events must still compile and work.

---

### STAGE 9 — Concurrency and the multithreaded notional machine (2 weeks)

**Concepts:** `std::thread`, `std::mutex`, `std::lock_guard`, `std::unique_lock`, `std::condition_variable`, `std::atomic`, the C++ memory model (briefly — full understanding is a multi-year project), `std::async`, `std::future`, lock-free intro. Race conditions, deadlocks, false sharing.

**Notional machine:** multiple threads each with their own stack, sharing the heap. Memory ordering as a constraint on what reorderings the compiler and CPU may do. This is genuinely hard and you should expect to be confused for the entire stage. That's normal.

**Tooling added:** ThreadSanitizer (`-fsanitize=thread`). Run every multithreaded program through it.

**Drill:**
- Implement a thread-safe queue with a mutex and condition variable. Break it on purpose (forget to lock, forget to notify) and watch TSan catch you.
- Implement a producer/consumer pair.
- Implement a single-producer/single-consumer lock-free ring buffer using atomics. (This is *hard*. It's also the canonical interview question for C++ systems roles.)

**Project:** *Multithreaded log scanner*. Tail one or more log files concurrently, run the IOC extractor against each line on a worker thread pool, write detections to a thread-safe output queue. Use the generic pipeline from stage 8.

**Reuse:** IOC extractor (stage 6), generic pipeline (stage 8).

**Anki cards added:** ~30.

**Gate:** given a multithreaded program with a planted race condition, find it using TSan, fix it, and explain in writing what would have happened in production without the fix. Do this for three different race types (read/write, write/write, missing memory order).

---

### STAGE 10 — Systems programming and the OS interface (3 weeks)

**Concepts (Windows-focused given target career):** the Win32 API surface, handles, `CreateFile`, `ReadFile`, `WriteFile`, `CreateProcess`, `OpenProcess`, `VirtualAlloc`, `VirtualProtect`, modules and `LoadLibrary`/`GetProcAddress`, the PE format at a high level, basic ETW concepts. Light coverage of the Linux equivalents (`open`/`read`/`mmap`/`fork`/`execve`/`/proc`) because the duality teaches you what is OS-specific vs universal.

**Notional machine:** processes, virtual address spaces, kernel vs user mode, syscalls. Read [the relevant chapters of *Windows Internals*](https://learn.microsoft.com/en-us/sysinternals/resources/windows-internals) — chapters 1, 3, 5 minimum. This is non-negotiable for the security track.

**Mode:** *heavy* worked-example study. The Windows API is enormous and you will be reading MSDN constantly. Build the habit of reading the docs *before* writing the call. Predict return values. Predict failure modes. Then run.

**Drill:** for each of `CreateFile`, `OpenProcess`, `VirtualAlloc`, `LoadLibrary`: write a tiny program that calls it, handles every documented failure mode, and frees its handle. Use `GetLastError` correctly. RAII-wrap each handle type — this is your first practical RAII at the OS boundary.

**Project:** *Process inspector*. CLI tool that takes a PID and prints: the process name, the loaded modules and their base addresses, the threads and their states, basic memory regions (using `VirtualQueryEx`). This is a tiny Process Hacker.

**Reuse:** you'll write a `Handle<T>` template — this is where stage 8's templates pay off.

**Anki cards added:** ~50, mostly Win32 idioms and error codes.

**Gate:** explain in writing what happens, in detail, when your code calls `CreateFile`. Cover: user-mode wrapper, syscall, kernel object, handle table, return path. If you can't, you don't yet understand the OS boundary well enough for security work.

---

### STAGE 11 — The PE format, ETW, and defensive tooling (4 weeks)

**Concepts:** PE/COFF structure (DOS header → NT headers → optional header → section headers → sections), imports, exports, relocations, the IAT, ETW providers and consumers, manifest-based vs TraceLogging providers. Light coverage of debug formats (PDB) and symbol resolution.

**Mode:** read the [PE format spec](https://learn.microsoft.com/en-us/windows/win32/debug/pe-format) and [ETW documentation](https://learn.microsoft.com/en-us/windows/win32/etw/about-event-tracing) directly. Pair every spec section with a code experiment. Don't read the whole spec then write code — read one section, write the code that exercises it, repeat.

**Drill:**
- Parse a PE file's headers and dump them to stdout. Compare to `dumpbin /headers`.
- Walk the import table and list every imported DLL and function.
- Subscribe to a built-in ETW provider (Microsoft-Windows-Kernel-Process is a good first one) and print events.

**Project A:** *PE parser*. Full PE parser as a library + CLI. Parses headers, sections, imports, exports. Outputs JSON. Has unit tests with hand-crafted PE blobs as fixtures.

**Project B:** *ETW process monitor*. Subscribes to kernel process and module-load events. Correlates them. Outputs a structured stream that the mini detection engine (stage 7/8) can consume.

**Reuse:** mini detection engine (stage 7), generic pipeline (stage 8), handle wrappers (stage 10).

**Anki cards added:** ~40.

**Gate:** given an arbitrary PE file, your parser produces output equivalent to `dumpbin /headers /imports /exports` for ≥95% of fields. Verified against a corpus of 50+ real binaries.

---

### STAGE 12 — Capstone portfolio and the publishing discipline (8–12 weeks)

You're now a junior C++ developer with a security focus. The remaining gap is *visible work* and the discipline of professional code review. This stage closes it.

**Concepts:** writing for other developers — README structure, doc comments (Doxygen), CMake at production quality, GitHub Actions CI with build matrix and sanitizers, semantic versioning, issue triage, PR review etiquette.

**Capstone projects (pick at least three; ship publicly):**

1. **Sigma → C++ rule engine.** Compile the open Sigma rule format into a runtime your detection engine can execute. This is the unified portfolio piece — it consumes everything: the parser (stage 2/6), the pipeline (stage 8), the threading (stage 9), the ETW source (stage 11), the rule abstraction (stage 7).

2. **Defensive shellcode loader analyzer.** A *defensive* tool that detects common shellcode loading patterns in a process — memory regions with `RWX` permissions, suspicious `VirtualAlloc` + `WriteProcessMemory` + `CreateRemoteThread` sequences via ETW. Write the post-mortem doc explaining what each pattern means and which legitimate software triggers false positives. This is a real detection engineering deliverable.

3. **DLL injection sandbox (research/learning).** A controlled DLL injector that only injects into a target process you own (a test harness you also wrote). The accompanying writeup explains every Win32 call, every failure mode, and why each EDR vendor cares about each one. *This is a learning tool, not an offensive one — frame it that way in your writeup and your portfolio.*

4. **Mini static analyzer.** Walk a small C subset's AST (use a parser generator or hand-roll a recursive-descent parser) and detect a small set of bugs (use-after-free on a single function's locals, unchecked return, format string with non-literal). This is the project that demonstrates you can build software *and* think about software.

**Discipline requirements for this stage:**
- Every project has a CI pipeline that builds on at least Linux + Windows, with ASan, UBSan, and TSan jobs.
- Every project has unit tests (use Catch2 or GoogleTest).
- Every project has a README written *as if explaining to your future employer* — what it does, why, how to build it, what you learned, what you'd do differently.
- Every project gets a public writeup (your blog, dev.to, or a GitHub gist linked from the repo).
- You open at least one PR against a real open-source C++ security project (Volatility, YARA, Sigma, Process Hacker, Mimikatz-defenders, BinaryNinja plugins, etc.) — even a small bugfix or doc PR. The skill of submitting a real PR is itself worth a stage.

**Gate (the final one):** can you describe, to a hiring manager, the architecture of one of your capstones — its components, their interfaces, the design tradeoffs you made, the bugs you hit, the things you'd refactor — for 30 minutes without notes, in a way that demonstrates you understand it deeply? Practice this with anyone who'll listen. Record yourself. The architecture interview is the bar for "professional programmer", and you can pass it.

---

## Part 5 — Execution scaffolding (the boring stuff that actually decides whether this works)

The research is unanimous on one thing: self-directed learners fail not from inability but from drift. The pipeline is engineered, but the execution is where it survives or dies.

**Daily structure:**
- Block 1 (90 min): new material — direct instruction + worked examples
- Break (20 min)
- Block 2 (90 min): drills — Parsons, completion, blank-page exercises
- Break + lunch (60 min)
- Block 3 (90 min): project work
- Break (20 min)
- Block 4 (60 min): code reading from a real codebase + Anki review

**Weekly:**
- Friday afternoon: write the self-explanation doc for the week's project; refactor one piece of week-old code; review Anki retention stats and re-read any cards with low retention.
- Sunday evening: 30-minute review of next week's stage, predict where you'll struggle.

**Monthly:**
- Re-attempt one gate from two months back, blank-page. Most "gone" knowledge isn't gone — it's just out of working memory and needs retrieval.
- Update the public progress log. The audience is you-six-months-from-now, who has forgotten everything.

**When stuck:**
- 30 minutes alone with the problem and the docs.
- Then: write down what you know, what you've tried, what you expect, what actually happens. The act of writing this often produces the answer.
- Then: rubber-duck (talk to yourself out loud, in full sentences).
- Then: search. Stack Overflow, cppreference, the standard, real source code on GitHub.
- Then, and only then: ask. The "stuck for 60+ minutes" rule is a feature, not a bug — debugging is the skill.

**Failure modes to actively prevent:**
- *Tutorial hell.* You will be tempted to start a new course/book/series before finishing the current one. Don't. The pipeline is the curriculum.
- *Switching languages.* You will hit a wall in stage 3 or stage 9 and want to learn Rust or Go because they "feel cleaner". This is the hardest part of the pipeline talking. Stay. The skills are 90% transferable but the discipline of finishing is the actual deliverable. Switching mid-pipeline is the single most common cause of self-taught learners not becoming professional programmers.
- *Project skip-ahead.* You will be tempted to start the shellcode loader before finishing the PE parser because it's cooler. Don't. The capstone derives its value from the chain.
- *Read-without-write.* The stages are heavy on reading early. Stay disciplined that you also write — but the ratio inverts over time. Stage 1 is 70% reading, stage 12 is 70% writing.
- *Skipping the gates.* The gates are not arbitrary checkpoints. They're the falsifiable evidence that you actually have the skill. Failing a gate and going back is *cheaper* than ignoring it and dragging an unfilled skill into the next stage.

---

## Part 6 — Why this pipeline produces a professional programmer

A professional programmer is not a person who knows a lot of language features. A professional programmer is a person who:

1. **Has accurate mental models of the machine.** Stages 0, 3, 5, 9, 10, 11 build this directly. Drawing memory, drawing the vtable, drawing the threads' stacks — these aren't pedagogical kitsch, they're how the model gets installed.

2. **Has a library of schemas, not a library of snippets.** Stages 2, 6, 7, 8 explicitly name and drill schemas. The graduate sees a problem and recognizes which of ~50 patterns it instantiates, then writes the code; they don't reinvent each time.

3. **Can read code as fluently as they write it.** Reading is foregrounded throughout, not assumed. By stage 12 the student has read more lines than they've written, by design.

4. **Debugs by hypothesis.** ASan/UBSan/TSan habits installed in stages 3 and 9 produce a debugger who *expects to see* the symptom of each bug class. This is the difference between a junior and a senior in any systems-language role.

5. **Ships finished software.** Every stage ends in a working artifact, not a tutorial completion. The capstone stage produces public artifacts that survive scrutiny.

6. **Knows when not to use a tool.** Stage 5 teaches when smart pointers are wrong. Stage 7 teaches when inheritance is wrong. Stage 8 teaches when templates are wrong. The graduate has *taste*, which is what separates a programmer from a code-typer.

7. **Can speak about their work.** The self-explanation discipline and the architecture-interview gate at stage 12 produce a person who can hold their own in a technical interview, a code review, and a design discussion.

If a motivated learner walks through these twelve stages — including failing and re-doing the gates honestly — the resulting human is a professional programmer in skill and knowledge. Not "a beginner with a job", which is what most bootcamp pipelines produce, but someone who understands what they're doing and why, and can pick up a new domain in C++ and be productive in days. That is the bar.

The pipeline is long. That's not a bug. The shortest path to a real skill is the one that doesn't skip steps.
