#ifndef IMAGEDIALOGCLIENT_H_INCLUDED
#define IMAGEDIALOGCLIENT_H_INCLUDED

class imageDialogClient
{
    public:
        virtual ~imageDialogClient(){};
        virtual void imageSelected(int i) = 0;
};

#endif // IMAGEDIALOGCLIENT_H_INCLUDED
