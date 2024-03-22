#ifndef BPMN_BaseElement_H
#define BPMN_BaseElement_H

#include "xml/bpmn/tBaseElement.h"
#include "Element.h"

namespace BPMN {

class ExtensionElements;
/**
 * @brief Base class for all core BPMN elements.
 *
 * The class allows to access the underlying XML element and may have associated extension elements.
 */
class BaseElement : public Element {
public:
  /// @brief Constructs a BaseElement object representing a BPMN element.
  BaseElement(XML::bpmn::tBaseElement* element);

  XML::bpmn::tBaseElement* element;

  /// @brief Id of element.
  std::string id;
  std::unique_ptr<ExtensionElements> extensionElements;

  /**
   * @brief Attempts to return the @ref element in the specified type T.
   * @return A pointer to casted object or `nullptr` if the cast fails
   */
  template<typename T> T* is() {
    return dynamic_cast<T*>(element);
  }

  /**
   * @brief Attempts to return the @ref element in the specified type T.
   * @return A pointer to casted object or `nullptr` if the cast fails
   */
  template<typename T> const T* is() const {
    return dynamic_cast<const T*>(element);
  }

  /**
   * @brief Casts the @ref element to the specified type T.
   * @return A pointer to casted object
   * @throws std::runtime_error if the cast fails
   */
  template<typename T = XML::bpmn::tBaseElement> T* get() {
    T* ptr = dynamic_cast<T*>(element); 
    if ( ptr == nullptr ) {
      throw std::runtime_error("Element: Illegal cast of element '" + (element->id.has_value() ? (std::string)element->id->get().value : "") + "'");
    }
    return ptr;
  }

  /**
   * @brief Casts the element to the specified type T.
   * @return A pointer to casted object
   * @throws std::runtime_error if the cast fails
   */
  template<typename T = XML::bpmn::tBaseElement> const T* get() const {
    const T* ptr = dynamic_cast<const T*>(element);
    if ( ptr == nullptr ) {
      throw std::runtime_error("Element: Illegal cast of element" + ( element->id.has_value() ? " '" + (std::string)element->id->get().value + "'" : "" ) );
    }
    return ptr;
  }
};

} // namespace BPMN

#endif // BPMN_BaseElement_H
