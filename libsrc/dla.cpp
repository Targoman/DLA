#include "dla.h"
#include <assert.h>
#include <sstream>
#include <set>

namespace Targoman
{
    namespace DLA
    {
        constexpr float MAX_RULER_THIN_SIZE = 4.f;
        constexpr float MIN_RULER_THICK_SIZE = 8.f;
        constexpr float MIN_RULER_ASPECT_RATIO = 4.f;

        void stuBoundingBox::unionWith_(const stuBoundingBox &_other)
        {
            float X0 = std::min(this->left(), _other.left());
            float Y0 = std::min(this->top(), _other.top());
            float X1 = std::max(this->right(), _other.right());
            float Y1 = std::max(this->bottom(), _other.bottom());
            *this = stuBoundingBox(X0, Y0, X1, Y1);
        }

        void stuBoundingBox::unionWith_(const BoundingBoxPtr_t &_other)
        {
            this->unionWith_(*_other);
        }

        stuBoundingBox stuBoundingBox::unionWith(const stuBoundingBox &_other) const
        {
            stuBoundingBox Union = *this;
            Union.unionWith(_other);
            return Union;
        }

        stuBoundingBox stuBoundingBox::unionWith(const BoundingBoxPtr_t &_other) const
        {
            return this->unionWith(*_other);
        }

        void stuBoundingBox::intersectWith_(const stuBoundingBox &_other)
        {
            float X0 = std::max(this->left(), _other.left());
            float Y0 = std::max(this->top(), _other.top());
            float X1 = std::min(this->right(), _other.right());
            float Y1 = std::min(this->bottom(), _other.bottom());
            *this = stuBoundingBox(X0, Y0, X1, Y1);
        }

        void stuBoundingBox::intersectWith_(const BoundingBoxPtr_t &_other)
        {
            this->intersectWith_(*_other);
        }

        stuBoundingBox stuBoundingBox::intersectWith(const stuBoundingBox &_other) const
        {
            stuBoundingBox Intersection = *this;
            Intersection.intersectWith_(_other);
            return Intersection;
        }

        stuBoundingBox stuBoundingBox::intersectWith(const BoundingBoxPtr_t &_other) const
        {
            return this->intersectWith(*_other);
        }

        float stuBoundingBox::horizontalOverlap(const stuBoundingBox &_other) const
        {
            float X0 = std::max(this->left(), _other.right());
            float X1 = std::min(this->right(), _other.right());
            return X1 - X0;
        }

        float stuBoundingBox::horizontalOverlap(const BoundingBoxPtr_t &_other) const
        {
            return this->horizontalOverlap(*_other);
        }

        float stuBoundingBox::verticalOverlap(const stuBoundingBox &_other) const
        {
            float Y0 = std::max(this->top(), _other.top());
            float Y1 = std::min(this->bottom(), _other.bottom());
            return Y1 - Y0;
        }

        float stuBoundingBox::verticalOverlap(const BoundingBoxPtr_t &_other) const
        {
            return this->verticalOverlap(*_other);
        }

        bool stuBoundingBox::isHorizontalRuler() const
        {
            return (this->height() < MAX_RULER_THIN_SIZE) && this->width() > std::max(MIN_RULER_THICK_SIZE, MIN_RULER_ASPECT_RATIO * this->height());
        }

        bool stuBoundingBox::isVerticalRuler() const
        {
            return (this->width() < MAX_RULER_THIN_SIZE) && this->height() > std::max(MIN_RULER_THICK_SIZE, MIN_RULER_ASPECT_RATIO * this->width());
        }

        DocBlockPtrVector_t analyseOverallStructure(const DocItemPtrVector_t &_items, float _width, float _height)
        {
            return DocBlockPtrVector_t();
        }

        clsDocBlockPtr analyseBlockAsText(const clsDocBlockPtr &_block)
        {
            return clsDocBlockPtr();
        }

        clsDocBlockPtr analyseBlockAsFigure(const clsDocBlockPtr &_block)
        {
            return clsDocBlockPtr();
        }

        clsDocBlockPtr analyseBlockAsTable(const clsDocBlockPtr &_block)
        {
            return clsDocBlockPtr();
        }

        clsDocBlockPtr analyseBlockAsFormulae(const clsDocBlockPtr &_block)
        {
            return clsDocBlockPtr();
        }

    }
}