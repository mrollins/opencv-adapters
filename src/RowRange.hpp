#ifndef CV_ADAPTERS_ROWRANGE_HPP
#define	CV_ADAPTERS_ROWRANGE_HPP

#include <iterator>
#include <opencv2/core/core.hpp>

namespace cv
{

template <typename T>
class RowRangeConstIterator : public std::iterator<std::forward_iterator_tag, T>
{
public:
    RowRangeConstIterator()
    : data()
    , row()
    , position()
    {}

    RowRangeConstIterator(const cv::Mat_<T>& m, const int index)
    : data(m)
    , row()
    , position(index)
    {
        CV_DbgAssert(position >= 0 && position <= data.rows);
    }

    // Dereference
    const cv::Mat_<T>& operator*() const
    {
        setRow();
        return row;
    }

    const cv::Mat_<T>* operator->() const
    {
        setRow();
        return &row;
    }

    // Logical comparison
    template <typename U>
    friend bool operator==(const RowRangeConstIterator<U>&, const RowRangeConstIterator<U>&);
    template <typename U>
    friend bool operator<(const RowRangeConstIterator<U>&, const RowRangeConstIterator<U>&);

    // Increment
    RowRangeConstIterator& operator++()
    {
        ++position;            
        return *this;
    }

    RowRangeConstIterator operator++(int)
    {
        RowRangeConstIterator tmp(*this);
        ++(*this);
        return tmp;
    }

protected:
    void setRow() const
    {
        row = data.row(position);
    }

    cv::Mat_<T> data;
    mutable cv::Mat_<T> row;
    int position;
};
    
template <typename T>
bool operator==(const RowRangeConstIterator<T>& left, const RowRangeConstIterator<T>& right)
{
    return left.position == right.position;
}

template <typename T>
bool operator!=(const RowRangeConstIterator<T>& left, const RowRangeConstIterator<T>& right)
{
    return !(left == right);
}

template <typename T>
bool operator<(const RowRangeConstIterator<T>& left, const RowRangeConstIterator<T>& right)
{
    return left.position < right.position;
}

template <typename T>
bool operator<=(const RowRangeConstIterator<T>& left, const RowRangeConstIterator<T>& right)
{
    return (left < right) || (left == right);
}

template <typename T>
bool operator>=(const RowRangeConstIterator<T>& left, const RowRangeConstIterator<T>& right)
{
    return !(left < right);
}

template <typename T>
bool operator>(const RowRangeConstIterator<T>& left, const RowRangeConstIterator<T>& right)
{
    return !(left <= right);
}

template <typename T>
class RowRangeIterator : public RowRangeConstIterator<T>
{
public:
    RowRangeIterator()
    : RowRangeConstIterator<T>()
    {}
    
    RowRangeIterator(const cv::Mat_<T>& m, const int index)
    : RowRangeConstIterator<T>(m, index)
    {}

    // Dereference
    cv::Mat_<T>& operator*() const
    {
        this->setRow();
        return this->row;
    }

    cv::Mat_<T>* operator->() const
    {
        this->setRow();
        return &this->row;
    }
};

template <typename T>
class RowRange
{
public:
    typedef RowRangeConstIterator<T> const_iterator;
    typedef RowRangeIterator<T> iterator;
    
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
        return const_iterator(data, data.rows);
    }
    
    iterator end()
    {
        return iterator(data, data.rows);
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

} // namespace cv

#endif	/* CV_ADAPTERS_ROWRANGE_HPP */

