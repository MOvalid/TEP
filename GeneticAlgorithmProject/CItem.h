#ifndef TEP_PROJEKT2_CITEM_H
#define TEP_PROJEKT2_CITEM_H


class CItem {
private:
    double value;
    double weight;

public:
    CItem(const double& newValue, const double& newWeight);
    CItem(const CItem& other);
    CItem(CItem&& other) noexcept;
    ~CItem();

    void setValue(const double& newValue);
    double getValue() const;

    void setWeight(const double& newWeight);
    double getWeight() const;

    CItem& operator=(const CItem& other);
    CItem& operator=(CItem&& other) noexcept;

};


#endif //TEP_PROJEKT2_CITEM_H
