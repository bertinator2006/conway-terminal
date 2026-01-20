# Conway's Game of Life Terminal Simulator - AI Agent Instructions

## Architecture Overview
This is a C-based terminal application implementing Conway's Game of Life with a double-buffered grid system. The core components are:
- **Board struct**: Contains two `uint8_t` grids (current and next state), width, and height
- **Cell representation**: Bit 7 indicates alive/dead state; lower 7 bits store neighbor count for optimization
- **Modules**: `conway.c/h` (game logic), `terminal.c/h` (I/O), `main.c` (entry point)

Key design decisions:
- Double buffering prevents race conditions during state updates
- 1D array storage with `y*width + x` indexing for cache efficiency
- Bit-packed cells reduce memory usage and enable fast neighbor counting

## Build and Run Workflow
- **Build**: `make all` compiles `src/*.c` into `./program` executable
- **Run**: `./program [optional_file]` 
  - Without file: Interactive terminal input for board dimensions and cell states
  - With file: Load initial state from text file (0=dead, 1=alive, rows separated by newlines)
- **Execution**: Infinite loop displaying board, incrementing state, waiting for Enter keypress

## Code Patterns and Conventions
- **Memory management**: All `Board` instances must be destroyed with `destroy_board()` to free grids
- **Grid access**: Use `cell_alive(board, x, y)` for state checks; direct array access for performance-critical code
- **File parsing**: Strict width consistency required; first pass determines dimensions, second pass loads data
- **State updates**: `increment_state()` applies Conway rules using pre-computed neighbor counts
- **Terminal I/O**: Custom functions for board printing (`[]`=alive, `--`=dead) and separator lines

## Common Tasks
- **Adding features**: Modify `increment_state()` for rule changes, extend `terminal.c` for new I/O modes
- **Debugging**: Use `info_board()` to inspect board metadata; add printf statements in update loops
- **Testing**: Create text files in root directory (e.g., `test.txt` format) for reproducible initial states
- **Performance**: Neighbor counting is pre-computed; avoid redundant `cell_alive()` calls in hot paths

## File Structure Reference
- `src/`: Current implementation (looping simulation)
- `old_src/`: Single-step version (for comparison/reference)
- `makefile`: Simple GCC compilation setup
- Text files: Board input format examples</content>
<parameter name="filePath">/home/aayush/conway-terminal/.github/copilot-instructions.md