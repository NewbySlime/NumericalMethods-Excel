#ifndef VAR_DATA_HEADER
#define VAR_DATA_HEADER

#include "vector"
#include "stdarg.h"


class VariadicData_linkedlist{
  public:
    struct linked_list{
      linked_list *next;
      void *data;
    };
  
  private:
    linked_list *_head = NULL;
    linked_list *_tail = NULL;

    linked_list *_currentll = NULL;

    linked_list *_createll(void *data = NULL){
      linked_list *res = new linked_list();
      res->next = NULL;
      res->data = data;

      return res;
    }
  
  public:
    VariadicData_linkedlist(){}

    ~VariadicData_linkedlist(){
      safe_delete();
    }

    void safe_delete(){
      linked_list *_ll = _head;
      while(_ll){
        delete _ll->data;

        linked_list *_l = _ll;
        _ll = _ll->next;
        delete _l;
      }

      _head = NULL;
      _tail = NULL;
      _currentll = NULL;
    }

    template<typename T> void add_tovar(T &data){
      T *_data = new T();
      memcpy(_data, &data, sizeof(T));

      linked_list *_ll = _createll(_data);
      if(!_head)
        _head = _ll;
      
      if(_tail)
        _tail->next = _ll;

      _tail = _ll;
    }

    template<typename T> T next(){
      if(_currentll){
        T *res = (T*)_currentll->data;
        _currentll = _currentll->next;
        return *res;
      }
      
      return T();
    }

    void init_var(){
      _currentll = _head;
    }
};

#endif