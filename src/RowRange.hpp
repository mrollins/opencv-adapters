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
        , position()
        {}

        RowRangeConstIterator(const cv::Mat_<T>& m, int index)
        : data(m)
        , position(index)
        {
            CV_DbgAssert(position >= 0 && position <= data.rows + 1);
            if (index != data.rows + 1) {
                row = m.row(index);
            }
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
        cv::Mat_<T> data;
        mutable cv::Mat_<T> row;
        int position;
    };
    
template <typename T>
class RowRangeIterator : public RowRangeConstIterator<T>
{
public:
    RowRangeIterator()
    : RowRangeConstIterator<T>()
    {}
    
    RowRangeIterator(const cv::Mat_<T>& m, int index)
    : RowRangeConstIterator<T>(m, index)
    {}

    // Dereference
    cv::Mat_<T>& operator*() const
    {
        return RowRangeConstIterator<T>::row;
    }

    cv::Mat_<T>* operator->() const
    {
        return &RowRangeConstIterator<T>::row;
    }
};

template <typename T>
class RowRange
{
public:
    typedef RowRangeConstIterator<T> const_iterator;
    typedef RowRangeIterator<T> iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
    typedef std::reverse_iterator<iterator> reverse_iterator;
    
    RowRange(cv::Mat m)
    : data(m)
    {
        CV_Assert(m.type() == cv::DataType<T>::type);
    }
    
    RowRange(cv::Mat_<T> m)
    : data(m) {}
    
    const_iterator begin() const
    {
        return const_iterator(data, 0);
    }
    
    iterator begin()
    {
        return iterator(data, 0);
    }
    
    const_iterator end() const
    {
        return const_iterator(data, data.rows + 1);
    }
    
    iterator end()
    {
        return iterator(data, data.rows + 1);
    }
    
    const_iterator cbegin() const
    {
        return begin();
    }
    
    const_iterator cend() const
    {
        return end();
    }

private:
    cv::Mat_<T> data;
};

template <typename T>
RowRange<T> make_RowRange(cv::Mat_<T> m)
{
    return RowRange<T>(m);
}

#endif	/* CV_ADAPTERS_ROWRANGE_HPP */

