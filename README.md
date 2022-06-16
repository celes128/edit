This is a library for editing any type of documents.
It uses interfaces for commands and documents.
There is a command history concrete class to support undo and redo operations.

## Sample code
```cpp
// Create a history with room for 16 commands.
// When the history becomes full, the commands are overwritten.
edit::CommandHistory	history(16);

// Let's suppose you have implemented a DocImage class...
class DocImage : public edit::IDocument {
	void SetPixel(Point p, Pixel pixel);
	Pixel GetPixel(Point p);
};

// ... along with a command to change a pixel.
class CmdSetPixel : public ICommand {
    edit::CommandOuput execute(edit::IDocument *doc) override;
    edit::CommandOuput undo(edit::IDocument *doc) override;
};

// ----------------------------------------------
// EXECUTE A COMMAND
// ----------------------------------------------
void App::OnClick(const MouseClickEvent &ev)
{
    auto *command = new CmdSetPixel(ev.position, Pixel{ CurrentColor() });
    
    // The history will execute and will be the owner of the pointer.
    m_history.execute(command);
}

// ----------------------------------------------
// UNDO/REDO A COMMAND
// ----------------------------------------------
void App::OnKeyPress(const KeyPressEvent &ev)
{
    switch (ev.key) {
        case 'Z': {
            if (ev.modifers & MOD_CTRL) {
                auto output = m_history.undo();
                
                // Process the command output...
            }
        }break;
        
        case 'Y': {
            if (ev.modifers & MOD_CTRL) {
                auto output = m_history.redo();
                
                // Process the command output...
            }
        }break;
        
        // ... other cases
    }
}
```