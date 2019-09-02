/*Abstract class of a Linear List*/
template<typename T>
class LinearList
{
public:
    virtual ~LinearList() {}                                 //virtual desctructor
    
    virtual bool empty() const=0;                           //if the list is empty
    virtual int size() const = 0;                           //return the number of elements in the list
    virtual T& get(int index) const=0;                      //return element[index]
    virtual int indexOf(const T& theElement) const=0;       //return the index of element, if not found, return -1
    virtual void erase(int index)=0;                        //delete element[index]
    virtual void insert(int index, const T& theElement)=0;  //all the elements following element[index] including element[index] right shift one position, element[index]=new element
    virtual void output(std::ostream& out) const=0;         //show all the elements
};