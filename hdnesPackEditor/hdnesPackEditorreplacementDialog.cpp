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
        float pixSize = coreData::cData->scale * hdImgScale;
        main::mForm->setReplacement(cboImage->GetSelection(), (selectedX - imgOffsetX - clickOffset.x) / hdImgScale, (selectedY - imgOffsetY - clickOffset.y) / hdImgScale);
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

    hdImgScale = min(((float)pnlImage->GetSize().x) / ((float)coreData::cData->images[cboImage->GetSelection()]->imageData.GetWidth()), ((float)pnlImage->GetSize().y) / ((float)coreData::cData->images[cboImage->GetSelection()]->imageData.GetHeight()));

    wxImage scaledImg;
    scaledImg = coreData::cData->images[cboImage->GetSelection()]->imageData.Scale(coreData::cData->images[cboImage->GetSelection()]->imageData.GetWidth() * hdImgScale, coreData::cData->images[cboImage->GetSelection()]->imageData.GetHeight() * hdImgScale);
    imgOffsetX = (pnlImage->GetSize().x - scaledImg.GetWidth()) / 2;
    imgOffsetY = (pnlImage->GetSize().y - scaledImg.GetHeight()) / 2;
    int mouseX = selectedX - imgOffsetX;
    int mouseY = selectedY - imgOffsetY;

    wxImage displayImg;
    displayImg = wxImage(pnlImage->GetSize(), true);
    displayImg.SetRGB(displayImg.GetSize(), 128, 0, 128);
    displayImg.Paste(scaledImg, imgOffsetX, imgOffsetY);

    wxPoint pt;
    wxPoint pt2;
    wxPoint tileBoxSize;
    float pixSize = coreData::cData->scale * hdImgScale;
    tileBoxSize.x = (8 * pixSize) - 1;
    tileBoxSize.y = tileBoxSize.x;

    if(chkSnapToGrid->IsChecked()){
        float rawOffsetX = (mouseX / pixSize) + selectedTiles[0].objCoordX - xOffSet;
        float rawOffsetY = (mouseY / pixSize) + selectedTiles[0].objCoordY - yOffSet;
        float adjustX = fmod(rawOffsetX, 8) * pixSize;
        float adjustY = fmod(rawOffsetY, 8) * pixSize;

        if(rawOffsetX >= 0){
            clickOffset.x = fmod(rawOffsetX, 8) * pixSize;
        }
        else{
            clickOffset.x = floor(fmod(rawOffsetX, 8) * pixSize);
        }
        if(rawOffsetY >= 0){
            clickOffset.y = fmod(rawOffsetY, 8) * pixSize;
        }
        else{
            clickOffset.y = floor(fmod(rawOffsetY, 8) * pixSize);
        }
    }
    else{
        clickOffset.x = 0;
        clickOffset.y = 0;
    }
    for(int i = 0; i < selectedTiles.size(); ++i){
        pt.x = ((selectedTiles[i].objCoordX - xOffSet) * pixSize) + selectedX - clickOffset.x;
        pt.y = ((selectedTiles[i].objCoordY - yOffSet) * pixSize) + selectedY - clickOffset.y;

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
