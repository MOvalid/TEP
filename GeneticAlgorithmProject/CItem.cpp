#include "CItem.h"
#include "CHelper.h"
#include "MyException/InvalidArgumentConstructorException.h"

CItem::CItem(const double& value, const double& weight): value(value), weight(weight){
    if(value <= 0.0) throw InvalidArgumentConstructorException(CHelper::generateErrorMessage("Positive double (value)", std::to_string(value)));
    if(weight <= 0.0) throw InvalidArgumentConstructorException(CHelper::generateErrorMessage("Positive double (weight)",  std::to_string(weight)));
}

CItem::CItem(const CItem& other): value(other.value), weight(other.weight){}

CItem::CItem(CItem&& other) noexcept : value(other.value), weight(other.weight){
    other.weight = 0;
    other.value = 0;
}

CItem::~CItem() = default;

void CItem::setValue(const double& newValue){
    if(newValue > 0.0) value = newValue;
}

double CItem::getValue() const {
    return value;
}

void CItem::setWeight(const double& newWeight){
    if(newWeight > 0.0) weight = newWeight;
}

double CItem::getWeight() const {
    return weight;
}

CItem& CItem::operator=(const CItem& other){
    value = other.value;
    weight = other.weight;
    return *this;
}

CItem& CItem::operator=(CItem&& other) noexcept {
    value = other.value;
    weight = other.weight;
    return *this;
}
