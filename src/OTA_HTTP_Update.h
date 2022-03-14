//=======================================================================================================================
//DIRETIVAS
//=======================================================================================================================

#ifndef OTAHTTPUPDATE_H
#define OTAHTTPUPDATE_H

void progresso(size_t atual, size_t total);

class OTAHTTPUpdate {
    private:
        String _linkSketch;
        String _linkSpiffs;
        
    public:
        OTAHTTPUpdate();
        void reboot();
        void setLinkSketch(String linkSketch);
        void setLinkSpiffs(String linkSpiffs);
        void setLedProgresso(int ledProgresso);

        int atualizarSketch();
        
        int atualizarSpiffs();
        int atualizarSpiffs(bool reboot);

        void resultado(int codigo);
};

#endif

//=======================================================================================================================
