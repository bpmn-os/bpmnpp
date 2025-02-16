#ifndef BPMN_ExtensionElements_H
#define BPMN_ExtensionElements_H

#include "Element.h"
#include "BaseElement.h"
#include "xml/bpmn/tExtensionElements.h"

namespace BPMN {

class BaseElement;

/**
 * @brief Base class for extension elements that may be provided for a BPMN element.
 */
class ExtensionElements : public Element {
public:
  ExtensionElements(XML::bpmn::tBaseElement* element);

  XML::bpmn::tExtensionElements* element;

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

  /**
   * @brief Returns a vector of elements of type T embedded within a container of type T.
   **/
  template<class C, class T> std::vector< std::reference_wrapper<const T> > get() const {
    if ( element ) {
      if ( auto container = element->template getOptionalChild<const C>(); container.has_value() ) {
        return container->get().template getChildren<const T>();
      }
    }
    return std::vector< std::reference_wrapper<const T> >(); 
  }

  /**
   * @brief Reference to the base element the extension elements are bound to.
   */
  BaseElement* baseElement;
private:
  /**
   * @brief Returns the @ref element if given or a `nullptr` otherwise.
   **/
  XML::bpmn::tExtensionElements* getExtensionElements(XML::bpmn::tBaseElement* element);

};

} // namespace BPMN

#endif // BPMN_ExtensionElements_H
