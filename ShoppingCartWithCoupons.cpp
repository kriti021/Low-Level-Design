#include <bits/stdc++.h>
using namespace std;

/*
Given shopping cart with product and coupons, calculate net price after 
applying coupons on products. Coupons can be of different types with certain conditions

1. N% off i.e. 10% off on all individuals
2. P% off on next time
3. D% off on nth item of type T

Sequentially want to apply all the coupons on the cart and get the total amount
*/

// Classes - Product, Coupon, ShoppingCart
// how will each of the discounts work - 

enum ProductType {
	ELECTRONIC,
	APPAREL,
	FASHION
};

class Product {
private:
	string name;
	ProductType productType;
	double price;
public:
	Product(string name, ProductType productType, double price) : name(name), productType(productType), price(price) {} // shorthand, sometimes more efficient
	string getName()
	{
		return(name);
	}
	ProductType getType()
	{
		return(productType);
	}
	double getPrice()
	{
		return(price);
	}
};

class Coupon {
public:
	virtual double applyCoupon(Product* product, int productCount) = 0;
};

class PercentOffCoupon : public Coupon {
private:
	int discountPercent;
public:
	PercentOffCoupon(int discountPercent) : discountPercent(discountPercent) {}
	double applyCoupon(Product *product, int productCount)
	{
		double originalPrice = product->getPrice() * productCount;
		return(originalPrice-(originalPrice*discountPercent)/100);
	}
};

class NthItemDiscount : public Coupon {
private:
	ProductType validProductType;
	int NValue;
	int discountPercent;
public:
	NthItemDiscount(ProductType validProductType, int NValue, int discountPercent) : validProductType(validProductType), NValue(NValue), discountPercent(discountPercent) {}
	double applyCoupon(Product *product, int productCount)
	{
		if (productCount < NValue || product->getType() != validProductType)
			return(product->getPrice());
		else
		{
			double originalPrice = product->getPrice();
			return(originalPrice*(productCount-1) + originalPrice-(originalPrice*discountPercent)/100);
		}
	}
};

class ShoppingCart {
private:
	map<Product*, int> productsMap;
	vector<Coupon*> coupons;
public:
	ShoppingCart(){}
	void addProduct(Product* product)
	{
		productsMap[product] += 1;
		cout<<"Added product "<<product->getName()<<" into cart. Total count = "<<productsMap[product]<<endl;
	}
	void removeProduct(Product* product)
	{
		productsMap[product] -= 1;
		cout<<"Removed product "<<product->getName()<<" into cart. Total count = "<<productsMap[product]<<endl;
		if (productsMap[product] == 0)
		{
			productsMap.erase(product);
		}
	}
	void addCoupon(Coupon *coupon)
	{
		coupons.push_back(coupon);
	}
	double calculateTotalPrice()
	{
		double totalCost = 0.0;
		for (auto itemCountPair: productsMap)
		{
			Product* item = itemCountPair.first;
			int count = itemCountPair.second;
			double discountedPrice = item->getPrice() * count;
			for (auto coupon: coupons)
			{
				discountedPrice = coupon->applyCoupon(item, count);
			}
			totalCost += discountedPrice;
		}
		return(totalCost);
	}
};

int main() {
	Product *p1 = new Product("cream", FASHION, 100); // -10
	Product *p2 = new Product("mobile", ELECTRONIC, 1000); // -100
	Product *p3 = new Product("jeans", APPAREL, 500); // -50
	
	ShoppingCart cart;
	cart.addProduct(p1);
	cart.addProduct(p2);
	cart.addProduct(p3);
	cart.addProduct(p1);
	
	cout<<"Total cost at checkout without discount: "<<cart.calculateTotalPrice()<<endl;
	
	PercentOffCoupon *coupon1 = new PercentOffCoupon(10);
	NthItemDiscount *coupon2 = new NthItemDiscount(ELECTRONIC, 1, 20);
	
	cart.addCoupon(coupon1);
	cart.addCoupon(coupon2);
	
	cout<<"Total cost at checkout with discount: "<<cart.calculateTotalPrice()<<endl;
	
	return 0;
}