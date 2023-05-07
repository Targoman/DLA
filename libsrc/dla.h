#ifndef __TARGOMAN_DLA__
#define __TARGOMAN_DLA__

#include <memory>
#include <limits>
#include <vector>
#include <string>

namespace Targoman
{
    namespace DLA
    {

        struct stuPoint
        {
            float X, Y;
            stuPoint(float _x = 0, float _y = 0) : X(_x), Y(_y) {}
        };

        struct stuSize
        {
            float Width;
            float Height;

            float area() const { return this->Width * this->Height; }

            stuSize(float _w = 0, float _h = 0) : Width(_w), Height(_h) {}
        };

        struct stuBoundingBox;
        typedef std::shared_ptr<stuBoundingBox> BoundingBoxPtr_t;
        struct stuBoundingBox
        {
            stuPoint Origin;
            stuSize Size;

            stuBoundingBox(const stuPoint &_origin, const stuSize &_size) : Origin(_origin), Size(_size) {}
            stuBoundingBox(float _x0, float _y0, float _x1, float _y1) : stuBoundingBox(stuPoint(_x0, _y0), stuSize(_x1 - _x0, _y1 - _y0)) {}
            stuBoundingBox(const stuPoint &_topLeft, const stuPoint &_bottomRight) : stuBoundingBox(_topLeft.X, _topLeft.Y, _bottomRight.X, _bottomRight.Y) {}

            float left() const { return this->Origin.X; }
            float top() const { return this->Origin.Y; }
            float right() const { return this->Origin.X + this->Size.Width; }
            float bottom() const { return this->Origin.Y + this->Size.Height; }

            float width() const { return this->Size.Width; }
            float height() const { return this->Size.Height; }

            float centerX() const { return this->Origin.X + this->Size.Width / 2; }
            float centerY() const { return this->Origin.Y + this->Size.Height / 2; }

            float area() const { return this->Size.area(); }

            void unionWith_(const stuBoundingBox &_other);
            void unionWith_(const BoundingBoxPtr_t &_other);

            stuBoundingBox unionWith(const stuBoundingBox &_other) const;
            stuBoundingBox unionWith(const BoundingBoxPtr_t &_other) const;

            void intersectWith_(const stuBoundingBox &_other);
            void intersectWith_(const BoundingBoxPtr_t &_other);

            stuBoundingBox intersectWith(const stuBoundingBox &_other) const;
            stuBoundingBox intersectWith(const BoundingBoxPtr_t &_other) const;

            float horizontalOverlap(const stuBoundingBox &_other) const;
            float horizontalOverlap(const BoundingBoxPtr_t &_other) const;

            float verticalOverlap(const stuBoundingBox &_other) const;
            float verticalOverlap(const BoundingBoxPtr_t &_other) const;

            bool isHorizontalRuler() const;
            bool isVerticalRuler() const;
        };

        enum class enuDocItemType
        {
            None,
            Image,
            Path,
            VirtualLine,
            Char,
            Background
        };

        enum class enuDocArea
        {
            Header,
            Body,
            Footer,
            LeftSidebar,
            RightSidebar,
            Watermark
        };

        struct stuDocItem
        {
            stuBoundingBox BoundingBox;
            enuDocItemType Type;
            int32_t RepetitionPageOffset;
            float Baseline, Ascent, Descent;
            wchar_t Char;
        };
        typedef std::shared_ptr<stuDocItem> DocItemPtr_t;
        typedef std::vector<DocItemPtr_t> DocItemPtrVector_t;

        enum class enuDocBlockType
        {
            Text,
            Figure,
            Table,
            Formulae
        };

        struct stuDocBlock
        {
            stuBoundingBox BoundingBox;
            enuDocArea Area;
            enuDocBlockType Type;
            DocItemPtrVector_t Elements;
        };

        struct stuDocTextBlock;
        struct stuDocFigureBlock;
        struct stuDocTableBlock;
        struct stuDocFormulaeBlock;
        class clsDocBlockPtr : public std::shared_ptr<stuDocBlock>
        {
            inline stuDocTextBlock *asText();
            inline stuDocFigureBlock *asFigure();
            inline stuDocTableBlock *asTable();
            inline stuDocFormulaeBlock *asFormulae();
        };

        typedef std::vector<clsDocBlockPtr> DocBlockPtrVector_t;

        enum class enuListType
        {
            None,
            Bulleted,
            Numbered
        };

        struct stuDocLine
        {
            stuBoundingBox BoundingBox;
            float Baseline;
            int32_t ID;
            enuListType ListType;
            float TextLeft;
            DocItemPtrVector_t Items;
        };
        typedef std::vector<stuDocLine> DocLineVector_t;

        enum class enuDocTextBlockAssociation
        {
            None,
            IsCaptionOf,
            IsInsideOf
        };
        struct stuDocTextBlock : public stuDocBlock
        {
            DocLineVector_t Lines;
            enuDocTextBlockAssociation Association;
            clsDocBlockPtr AssociatedBlock;
        };

        struct stuDocFigureBlock : public stuDocBlock
        {
            clsDocBlockPtr Caption;
        };

        struct stuDocTableCell
        {
            clsDocBlockPtr Text;
            int16_t Row, RowSpan;
            int16_t Col, ColSpan;
        };
        typedef std::vector<stuDocTableCell> stuDocTableCellVector_t;
        struct stuDocTableBlock : public stuDocBlock
        {
            clsDocBlockPtr Caption;
            stuDocTableCellVector_t Cells;
        };

        struct stuDocFormulaeBlock : public stuDocBlock
        {
            std::wstring LatexSource;
        };

        inline stuDocTextBlock *clsDocBlockPtr::asText() { return static_cast<stuDocTextBlock *>(this->get()); }
        inline stuDocFigureBlock *clsDocBlockPtr::asFigure() { return static_cast<stuDocFigureBlock *>(this->get()); }
        inline stuDocTableBlock *clsDocBlockPtr::asTable() { return static_cast<stuDocTableBlock *>(this->get()); }
        inline stuDocFormulaeBlock *clsDocBlockPtr::asFormulae() { return static_cast<stuDocFormulaeBlock *>(this->get()); }

        DocBlockPtrVector_t analyseOverallStructure(const DocItemPtrVector_t &_items, float _width, float _height);

        clsDocBlockPtr analyseBlockAsText(const clsDocBlockPtr &_block);
        clsDocBlockPtr analyseBlockAsFigure(const clsDocBlockPtr &_block);
        clsDocBlockPtr analyseBlockAsTable(const clsDocBlockPtr &_block);
        clsDocBlockPtr analyseBlockAsFormulae(const clsDocBlockPtr &_block);

    }
}

#endif // __TARGOMAN_DLA__