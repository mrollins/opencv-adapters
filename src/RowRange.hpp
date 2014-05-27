#ifndef CV_ADAPTERS_ROWRANGE_HPP
#define	CV_ADAPTERS_ROWRANGE_HPP

#include <iterator>
#include <opencv2/core/core.hpp>

template <typename T>
class RowRangeConstIterator : public std::iterator<std::forward_iterator_tag, T>
    {
    public:
        RowRangeConstIterator()
        : data()
        , row()
        , position(0)
        {}

        RowRangeConstIterator(const cv::Mat_<T>& m, int index)
        : data(m)
        , row(data.row(index))
        , position(index)
        {
            CV_DbgAssert(position >= 0 && position <= data.rows + 1);
        }
        
        // Dereference
        const cv::Mat_<T>& operator*() const
        {
            return row;
        }
        
        const cv::Mat_<T>* operator->() const
        {
            return &row;
        }
        
        // Logical comparison
        bool operator==(const RowRangeConstIterator& that) const
        {
            return this->position == that.position;
        }

        bool operator!=(const RowRangeConstIterator& that) const
        {
            return !(*this == that);
        }
        
        bool operator<(const RowRangeConstIterator& that) const
        {
            return this->position < that.position;
        }
        
        bool operator>(const RowRangeConstIterator& that) const
        {
            return this->position > that.position;
        }
        
        bool operator<=(const RowRangeConstIterator& that) const
        {
            return !(*this > that);
        }
        
        bool operator>=(const RowRangeConstIterator& that) const
        {
            return !(*this < that);
        }
        
        // Increment
        RowRangeConstIterator& operator++()
        {
            ++position;
            return *this;
        }
        
        RowRangeConstIterator operator++(int) const
        {
            RowRangeConstIterator tmp(*this);
            ++(*this);
            return tmp;
        }
        
        

    protected:
        const cv::Mat_<T>& data;
        mutable cv::Mat_<T> row;
        int position;
    };
    
template <typename T>
class RowRangeIterator : public RowRangeConstIterator
{
public:
    RowRangeIterator(const cv::Mat_<T>& m, int position)
    : RowRangeConstIterator(m, position)
    {}

};

template <typename T>
class RowRange
{
public:
    typedef RowRangeConstIterator const_iterator;
    typedef RowRangeIterator iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
    typedef std::reverse_iterator<iterator> reverse_iterator;
    
    RowRange(cv::Mat m)
    : data(m)
    {
        CV_Assert(m.type() == cv::DataType<T>::type);
    }
    
    RowRange(cv::Mat_<T> m)
    : data(m) {}
    
    
    


private:
    cv::Mat_<T> data;
    cv::Range range;
};

#endif	/* CV_ADAPTERS_ROWRANGE_HPP */

