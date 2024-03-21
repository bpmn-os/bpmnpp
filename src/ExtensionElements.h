#ifndef BPMN_ExtensionElements_H
#define BPMN_ExtensionElements_H

#include <stdexcept>
#include "xml/bpmn/tBaseElement.h"
#include "xml/bpmn/tExtensionElements.h"

namespace BPMN {

class BaseElement;

/**
 * @brief Base class for extension elements that may be provided for a BPMN element.
 */
class ExtensionElements {
public:
  ExtensionElements(XML::bpmn::tBaseElement* element);
  virtual ~ExtensionElements();

  /**
   * @brief Attempts to cast the object to the specified type T.
   * @return A pointer to casted object or `nullptr` if the cast fails
   */
  template<typename T> T* represents() {
    return dynamic_cast<T*>(this);
  }

  /**
   * @brief Attempts to cast the object to the specified type T.
   * @return A pointer to casted object or `nullptr` if the cast fails
   */
  template<typename T> const T* represents() const {
    return dynamic_cast<const T*>(this);
  }

  /**
   * @brief Casts the object to the specified type T.
   * @return A pointer to casted object
   * @throws std::runtime_error if cast fails
   */
  template<typename T> T* as() {
    T* ptr = dynamic_cast<T*>(this); 
    if ( ptr == nullptr ) {
      throw std::runtime_error("ExtensionElements: Illegal cast");
    }
    return ptr; 
  }

  /**
   * @brief Casts the object to the specified type T.
   * @return A pointer to casted object
   * @throws std::runtime_error if cast fails
   */
  template<typename T> const T* as() const {
    const T* ptr = dynamic_cast<const T*>(this);
    if ( ptr == nullptr ) {
      throw std::runtime_error("ExtensionElements: Illegal cast");
    }
    return ptr;
  }

  /**
   * @brief Returns the @ref element if given or a `nullptr` otherwise.
   **/
  XML::bpmn::tExtensionElements* getExtensionElements(XML::bpmn::tBaseElement* element);

  /**
   * @brief Returns a vector of elements of type T embedded within a container of type T.
   **/
  template<class C, class T> std::vector< std::reference_wrapper<T> > get() {
   if ( element ) {
       if ( auto container = element->template getOptionalChild<C>(); container.has_value() ) {
        return container->get().template getChildren<T>();
      }
    }
    return std::vector< std::reference_wrapper<T> >(); 
  }

  XML::bpmn::tExtensionElements* element;

  /**
   * @brief Reference to the base element the extension elements are bound to.
   */
  BaseElement* baseElement;

};

} // namespace BPMN

#endif // BPMN_ExtensionElements_H
