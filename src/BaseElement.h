#ifndef BPMN_BaseElement_H
#define BPMN_BaseElement_H

#include "xml/bpmn/tBaseElement.h"
#include <memory>
#include <vector>
#include <optional>
#include <functional>

namespace BPMN {

class ExtensionElements;
/**
 * @brief Base class for all elements in a BPMN model.
 *
 * The class encapsulates the information and relationships associated with an element in a BPMN process.
 * The class allows to access the underlying XML element and may have associated extension elements.
 */
class BaseElement {
public:
  /// @brief Constructs a BaseElement object representing a BPMN element.
  BaseElement(XML::bpmn::tBaseElement* element);

  virtual ~BaseElement() = default;

  /// @brief Id of element.
  std::string id;

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
      throw std::runtime_error("BaseElement: Illegal cast of element '" + (element->id.has_value() ? (std::string)element->id->get().value : "") + "'");
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
      throw std::runtime_error("BaseElement: Illegal cast of element '" + (element->id.has_value() ? (std::string)element->id->get().value : "") + "'");
    }
    return ptr;
  }

  /**
   * @brief Attempts to cast the element to the specified type T.
   * @return A pointer to casted object or `nullptr` if the cast fails
   */
  template<typename T> T* represents() {
    return dynamic_cast<T*>(this);
  }

  /**
   * @brief Attempts to cast the element to the specified type T.
   * @return A pointer to casted object or `nullptr` if the cast fails
   */
  template<typename T> const T* represents() const {
    return dynamic_cast<const T*>(this);
  }

  /**
   * @brief Casts the element to the specified type T.
   * @return A pointer to casted object
   * @throws std::runtime_error if cast fails
   */
  template<typename T> T* as() {
    T* ptr = dynamic_cast<T*>(this);
    if ( ptr == nullptr ) {
      throw std::runtime_error("BaseElement: Illegal cast of element '" + this->id + "'");
    }
    return ptr;
  }

  /**
   * @brief Casts the element to the specified type  T.
   * @return A pointer to casted object
   * @throws std::runtime_error if cast fails
   */
  template<typename T> const T* as() const {
    const T* ptr = dynamic_cast<const T*>(this);
    if ( ptr == nullptr ) {
      throw std::runtime_error("BaseElement: Illegal cast of element '" + this->id + "'");
    }
    return ptr;
  }

  XML::bpmn::tBaseElement* element;

  std::unique_ptr<ExtensionElements> extensionElements;
};

} // namespace BPMN

#endif // BPMN_BaseElement_H
