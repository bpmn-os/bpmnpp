#ifndef BPMN_ExtensionElements_H
#define BPMN_ExtensionElements_H

#include <stdexcept>
#include "xml/bpmn/tBaseElement.h"
#include "xml/bpmn/tExtensionElements.h"

namespace BPMN {

/**
 * @brief Represents a virtual class that can be overwritten to provide direct access to specific extension elements.
 */
class ExtensionElements {
public:
  ExtensionElements(XML::bpmn::tBaseElement* baseElement);
  virtual ~ExtensionElements();

  /// Returns a pointer of type T of the ExtensionElements.
  template<typename T> T* represents() {
    return dynamic_cast<T*>(this);
  }

  /**
   * Attempt to downcast the ExtensionElements to a derived class T.
   * If the cast fails, throws a std::runtime_error with an error message
   * indicating an illegal cast operation.
   */
  template<typename T> T* as() {
    T* ptr = dynamic_cast<T*>(this); 
    if ( ptr == nullptr ) {
      throw std::runtime_error("ExtensionElements: Illegal downcast");
    }
    return ptr; 
  };

  /**
   * Returns a the extension elements if they are given or a nullptr otherwise.
   **/
  XML::bpmn::tExtensionElements* getExtensionElements(XML::bpmn::tBaseElement* baseElement);

  /**
   * Returns a vector of elements of type T embedded within a container of type T.
   **/
  template<class C, class T> std::vector< std::reference_wrapper<T> > get() {
    if ( element ) {
      if ( auto container = element->template getOptionalChild<C>() ) {
        return container->get().template getChildren<T>();
      }
    }
    return std::vector< std::reference_wrapper<T> >(); 
  };

  XML::bpmn::tExtensionElements* element;

};

} // namespace BPMN

#endif // BPMN_ExtensionElements_H
