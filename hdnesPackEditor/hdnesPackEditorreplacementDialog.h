#ifndef __hdnesPackEditorreplacementDialog__
#define __hdnesPackEditorreplacementDialog__

/**
@file
Subclass of replacementDialog, which is generated by wxFormBuilder.
*/

#include "mainForm.h"

//// end generated include
#include "gameTile.h"

/** Implementing replacementDialog */
class hdnesPackEditorreplacementDialog : public replacementDialog
{
	protected:
		// Handlers for replacementDialog events.
		void imageSelected( wxCommandEvent& event );
        void mouseClicked( wxMouseEvent& event );
        void mouseMoved( wxMouseEvent& event );
        void sizeChanged( wxSizeEvent& event );
		void replacementConfirm( wxCommandEvent& event );
	public:
		/** Constructor */
		hdnesPackEditorreplacementDialog( wxWindow* parent );
	//// end generated class members
        vector<gameTile> selectedTiles;
        int xOffSet;
        int yOffSet;
        bool locationSelected;
        int selectedX;
        int selectedY;
        int imgOffsetX;
        int imgOffsetY;
        int scaledX;
        int scaledY;

        void setSelectedTiles(vector<gameTile> tiles, int pXOffSet, int pYOffSet);
        void showImage();
};

#endif // __hdnesPackEditorreplacementDialog__
