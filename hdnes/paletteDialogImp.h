#pragma once
#include "..\wxwidget\formhdnes.h"
#include "video.h"

class paletteDialogImp :
	public paletteDialog
{
private:
	int selectedX;
	int selectedY;
public:
	paletteDialogImp(void);
	~paletteDialogImp(void);

	void paletteCellSelected( wxMouseEvent& event );
	void newColorSelected( wxColourPickerEvent& event );
	void paletteFileSelected( wxFileDirPickerEvent& event );
	void paletteRepaint( wxPaintEvent& event );
	void refreshPalette(wxDC* dc);
	void showSelectedCellColor();
};

