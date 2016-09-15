#ifndef CORE_PART_H
#define CORE_PART_H


class core_part
{
    public:
        core_part();
        ~core_part();

        virtual void reset() = 0;
        virtual void saveState(fstream* statefile) = 0;
        virtual void loadState(fstream* statefile) = 0;

    protected:

    private:
};

#endif // CORE_PART_H
