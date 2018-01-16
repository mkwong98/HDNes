#include "hdnesPackEditorreplacementDialog.h"
#include "coreData.h"
#include "image.h"

hdnesPackEditorreplacementDialog::hdnesPackEditorreplacementDialog( wxWindow* parent )
:
replacementDialog( parent )
{
    if(coreData::cData){
        for(int i = 0; i < coreData::cData->images.size(); ++i){
            cboImage->Append(wxString(coreData::cData->images[i]->fileName.c_str()));
        }
    }
}

void hdnesPackEditorreplacementDialog::imageSelected( wxCommandEvent& event ){
    showImage();
}

void hdnesPackEditorreplacementDialog::replacementConfirm( wxCommandEvent& event )
{
// TODO: Implement replacementConfirm
}

void hdnesPackEditorreplacementDialog::mouseClicked( wxMouseEvent& event ){
}

void hdnesPackEditorreplacementDialog::mouseMoved( wxMouseEvent& event ){
}

void hdnesPackEditorreplacementDialog::sizeChanged( wxSizeEvent& event ){
}


void hdnesPackEditorreplacementDialog::setSelectedTiles(vector<gameTile> tiles){
    selectedTiles = tiles;
}

void hdnesPackEditorreplacementDialog::showImage(){
    float hdImgScale = min(((float)pnlImage->GetSize().x) / ((float)coreData::cData->images[cboImage->GetSelection()]->imageData.GetWidth()), ((float)pnlImage->GetSize().y) / ((float)coreData::cData->images[cboImage->GetSelection()]->imageData.GetHeight()));

    wxImage scaledImg;
    scaledImg = coreData::cData->images[cboImage->GetSelection()]->imageData.Scale(coreData::cData->images[cboImage->GetSelection()]->imageData.GetWidth() * hdImgScale, coreData::cData->images[cboImage->GetSelection()]->imageData.GetHeight() * hdImgScale);

    wxImage displayImg;
    displayImg = wxImage(pnlImage->GetSize(), true);
    displayImg.SetRGB(displayImg.GetSize(), 128, 0, 128);
    displayImg.Paste(scaledImg, (pnlImage->GetSize().x - scaledImg.GetWidth()) / 2, (pnlImage->GetSize().y - scaledImg.GetHeight()) / 2);

    wxBitmap bmp = wxBitmap(displayImg);
	if(bmp.IsOk()){
		wxClientDC* objDC;
		objDC = new wxClientDC(pnlImage);
		objDC->DrawBitmap(bmp, 0, 0);
		delete objDC;
	}
}
