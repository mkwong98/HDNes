#ifndef COLOURDIALOGCLIENT_H
#define COLOURDIALOGCLIENT_H


class colourDialogClient
{
    public:
        virtual ~colourDialogClient(){};
        virtual void colourSelected(Uint8) = 0;
};

#endif // COLOURDIALOGCLIENT_H
