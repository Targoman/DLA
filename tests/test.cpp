// Ignore PDFium warnings to stay vigilant about our own codes warnings
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wattributes"
#include <fpdfapi/fpdfapi.h>
#include <fpdfapi/fpdf_module.h>
#include <fpdfapi/fpdf_page.h>
#include <fxcodec/fx_codec.h>
#include <fxcrt/fx_coordinates.h>
#include <fpdfdoc/fpdf_doc.h>
#pragma GCC diagnostic pop

#include <string>
#include <string_view>
#include <fstream>
#include <memory>
#include <map>

#include <dla.h>
using namespace Targoman::DLA;

void initializePdfiumModules()
{
    CPDF_ModuleMgr::Create();
    CFX_GEModule::Create();

    auto Codec = CCodec_ModuleMgr::Create();
    CFX_GEModule::Get()->SetCodecModule(Codec);
    CPDF_ModuleMgr::Get()->SetCodecModule(Codec);

    CPDF_ModuleMgr::Get()->InitPageModule();
    CPDF_ModuleMgr::Get()->InitRenderModule();
    CPDF_ModuleMgr::Get()->SetDownloadCallback(nullptr);
}

std::vector<uint8_t> readFileContents(const char *_filePath)
{
    std::ifstream File(_filePath);
    File.seekg(0, std::ios_base::end);
    size_t FileSize = File.tellg();

    std::vector<uint8_t> FileContents(FileSize);
    File.read(reinterpret_cast<char *>(FileContents.data()), FileSize);
}

class clsPdfiumWrapper
{
private:
    std::shared_ptr<CPDF_Parser> Parser;
    std::map<size_t, CPDF_Page *> LoadedPages;

    CPDF_Page *getPage(size_t _pageIndex)
    {
        if (this->LoadedPages.find(_pageIndex) != this->LoadedPages.end())
            return this->LoadedPages[_pageIndex];
        auto Page = new ::CPDF_Page;
        Page->Load(this->Parser->GetDocument(), this->Parser->GetDocument()->GetPage(_pageIndex));
        Page->ParseContent();
        this->LoadedPages[_pageIndex] = Page;
        return Page;
    }

public:
    clsPdfiumWrapper(uint8_t *_data, size_t _size) : Parser(new CPDF_Parser)
    {
        Parser->StartParse(FX_CreateMemoryStream(_data, _size));
    }

};

int main(void)
{
    const std::string_view PDF_FILE_PATH("/data/Resources/Pdfs4LA/pdfs/col-2/bi-1000.pdf");
    auto PdfFileContent = readFileContents(PDF_FILE_PATH.data());

    initializePdfiumModules();

    auto PdfParser = std::make_shared<CPDF_Parser>();
    PdfParser->StartParse(FX_CreateMemoryStream(PdfFileContent.data(), PdfFileContent.size()));

    return 0;
}