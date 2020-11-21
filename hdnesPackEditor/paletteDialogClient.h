#ifndef PALETTEDIALOGCLIENT_H_INCLUDED
#define PALETTEDIALOGCLIENT_H_INCLUDED

class paletteDialogClient
{
    public:
        virtual ~paletteDialogClient(){};
        virtual void paletteSelected(Uint8* p) = 0;
};

#endif // PALETTEDIALOGCLIENT_H_INCLUDED
