This is a library for editing any type of documents.
It uses interfaces for commands and documents.
There is a command history concrete class to support undo and redo operations.

## Sample code
```cpp
// Create a history with room for 16 commands
// When the history becomes full, the commands are overwritten.
edit::CommandHistory	h(16);

// CmdCutSelection would be a concrete class that you implement.
class CmdCutSelection : public ICommand { };

// Executing a command stores it in the history.
h.execute(new CmdCutSelection(/*args*/));

// Cancel the "cut selection".
h.undo();

// Redo it.
h.redo();
```