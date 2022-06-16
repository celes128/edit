This is a library for editing any type of documents.
It uses interfaces for commands and documents.
There is a command history concrete class to support undo and redo operations.

## Sample code
```cpp
// Let's use a paint program as an example.

class App {
public:
    // Let's set the history capacity to 16.
    // When 16 commands are executed, the history is full
    // and starts overwriting them.
    App()
        : m_history(16)
    {}
    
    // PaintColor returns the current/selected color used to paint with the pen or bucket tool.
    color PaintColor() const;
    
    // Event handlers
    void OnClick(const MouseClickEvent &ev);
    void OnKeyPress(const KeyPressEvent &ev)
    
private:
    edit::CommandHistory	m_history;
};

// We need a concrete document class that implements IDocument.
// The directory tests/ contains the implementation of the following DocImage class.
class DocImage : public edit::IDocument {
public:
    /* Ctor omitted. */
    
    // This function will be called by our command CmdSetPixel that is defined below.
	void SetPixel(Point p, Pixel pixel);
	
	/* Other functions omitted. */
	
private:
    /* Data members omitted. */
};

// Now we implement a concrete command class to change a pixel of an image.
// The full implementation is also available in the tests/ directory.
class CmdSetPixel : public ICommand {
    edit::CommandOuput execute(edit::IDocument *doc) override;
    edit::CommandOuput undo(edit::IDocument *doc) override;
    
private:
	// Position of the pixel in the image.
	Point	m_p;

    // The pixel to write.
	Pixel	m_newPixel;
	
	// The pixel that was on the original image at position m_p.
	Pixel	m_originalPixel;
};

// ----------------------------------------------
// EXECUTE A COMMAND
// ----------------------------------------------
void App::OnClick(const MouseClickEvent &ev)
{
    auto *command = new CmdSetPixel(ev.position, Pixel{ PaintColor() });
    
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
                // For example, write "Undo!" on a status bar at the bottom of the application window.
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