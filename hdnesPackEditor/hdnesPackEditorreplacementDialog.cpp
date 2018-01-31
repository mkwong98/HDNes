#include "hdnesPackEditorreplacementDialog.h"
#include "hdnesPackEditormainForm.h"
#include "coreData.h"
#include "image.h"
#include "main.h"


hdnesPackEditorreplacementDialog::hdnesPackEditorreplacementDialog( wxWindow* parent )
:
replacementDialog( parent )
{
    locationSelected = false;
    if(coreData::cData){
        for(int i = 0; i < coreData::cData->images.size(); ++i){
            cboImage->Append(wxString(coreData::cData->images[i]->fileName.c_str()));
        }
    }
}

void hdnesPackEditorreplacementDialog::imageSelected( wxCommandEvent& event ){
    showImage();
}

void hdnesPackEditorreplacementDialog::replacementConfirm( wxCommandEvent& event ){
    if(locationSelected){
        main::mForm->setReplacement(cboImage->GetSelection(), scaledX, scaledX);
    }
    Show(false);
}

void hdnesPackEditorreplacementDialog::mouseClicked( wxMouseEvent& event ){
    if(cboImage->GetSelection() == wxNOT_FOUND) return;
    locationSelected = !locationSelected;
}

void hdnesPackEditorreplacementDialog::mouseMoved( wxMouseEvent& event ){
    if(!locationSelected){
        selectedX = event.GetPosition().x;
        selectedY = event.GetPosition().y;
        showImage();
    }
}

void hdnesPackEditorreplacementDialog::sizeChanged( wxSizeEvent& event ){
    showImage();
}


void hdnesPackEditorreplacementDialog::setSelectedTiles(vector<gameTile> tiles, int pXOffSet, int pYOffSet){
    selectedTiles = tiles;
    xOffSet = pXOffSet;
    yOffSet = pYOffSet;
}

void hdnesPackEditorreplacementDialog::showImage(){
    if(cboImage->GetSelection() == wxNOT_FOUND) return;

    //calculate image location
    float hdImgScale = min(((float)pnlImage->GetSize().x) / ((float)coreData::cData->images[cboImage->GetSelection()]->imageData.GetWidth()), ((float)pnlImage->GetSize().y) / ((float)coreData::cData->images[cboImage->GetSelection()]->imageData.GetHeight()));
    wxImage scaledImg;
    scaledImg = coreData::cData->images[cboImage->GetSelection()]->imageData.Scale(coreData::cData->images[cboImage->GetSelection()]->imageData.GetWidth() * hdImgScale, coreData::cData->images[cboImage->GetSelection()]->imageData.GetHeight() * hdImgScale);
    imgOffsetX = (pnlImage->GetSize().x - scaledImg.GetWidth()) / 2;
    imgOffsetY = (pnlImage->GetSize().y - scaledImg.GetHeight()) / 2;

    //show the image
    wxImage displayImg;
    displayImg = wxImage(pnlImage->GetSize(), true);
    displayImg.SetRGB(displayImg.GetSize(), 128, 0, 128);
    displayImg.Paste(scaledImg, imgOffsetX, imgOffsetY);

    wxPoint pt;
    wxPoint pt2;
    int scaledTileSize = 8 * coreData::cData->scale;
    wxPoint tileBoxSize;
    tileBoxSize.x = (scaledTileSize * hdImgScale) - 1;
    tileBoxSize.y = tileBoxSize.x;


    scaledX = (selectedX - imgOffsetX) / hdImgScale;
    scaledY = (selectedY - imgOffsetY) / hdImgScale;
    if(chkSnapToGrid->IsChecked()){
        scaledX -= fmod(scaledX, scaledTileSize);
        scaledY -= fmod(scaledY, scaledTileSize);
    }

    for(int i = 0; i < selectedTiles.size(); ++i){
        pt.x = (((selectedTiles[i].objCoordX - xOffSet) * coreData::cData->scale) + scaledX) * hdImgScale + imgOffsetX;
        pt.y = (((selectedTiles[i].objCoordY - yOffSet) * coreData::cData->scale) + scaledY) * hdImgScale + imgOffsetY;

        pt2 = pt;
        ++(pt2.x);
        ++(pt2.y);
        main::drawRect(displayImg, pt2, tileBoxSize, wxColour(0, 0, 0));
        main::drawRect(displayImg, pt, tileBoxSize, wxColour(255, 255, 255));
    }

    wxBitmap bmp = wxBitmap(displayImg);
	if(bmp.IsOk()){
		wxClientDC* objDC;
		objDC = new wxClientDC(pnlImage);
		objDC->DrawBitmap(bmp, 0, 0);
		delete objDC;
	}
}
