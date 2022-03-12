//=======================================================================================================================
//DIRETIVAS
//=======================================================================================================================

#ifndef OTAHTTPUPDATE_h
#define OTAHTTPUPDATE_h

void progresso(size_t atual, size_t total);

class OTAHTTPUpdate {
    private:
        String _linkSketch;
        String _linkSpiffs;
        //static void progresso(size_t atual, size_t total);
        
    public:
        OTAHTTPUpdate();
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
