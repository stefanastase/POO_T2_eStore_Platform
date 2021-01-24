# eStore Platform

Aplicatia implementeaza un sistem pentru o platforma online dedicata vanzarii de produse diverse.

Entitatile principale sunt **Produsele**, **Utilizatorii** si **Serverul** care stocheaza detalii despre produse si utilizatori si unde se pot efectua diverse operatii asupra entitatilor, precum căutări de produse, de utilizatori sau modificări de diferite cantități (adăugare sau scoatere de produse din coș).

## Structura si implementare

### Ierarhia Product

!(product_uml.jpg)

Cea mai complicata ierarhie de clase din proiect, include clasa abstracta `Product` din care se deriveaza 2 tipuri principale de produse: `NonFoodProduct` si `FoodProduct`. 

Printre produsele nelimentare putem regasi si produse reduse, `DiscountedProduct`, sau produse returnate, `ReturnedProduct`.

De asemenea, un produs returnat poate fi revandut la un pret redus: `ResealedProduct `(aflat in relatie de mostenire multipla cu `DiscountedProduct` si `ReturnedProduct`).

Toate clasele ierarhiei contin constructori cu si fara parametri, constructori de copiere, supradefinirea operatorului de atribuire, gettere, respectiv settere pentru atributele  membre.

Pe langa cele enumerate mai sus, clasa abstracta `Product` contine:
- un destructor virtual
- metoda virtuala `string getProductType()`, folosita in clasele subordonate pentru a determina tipul produsului
- meteoda virtuala `void display()`, folosita pentru afisarea produsului
- metoda virtuala `json toJSON()`. 

De asemenea, exista metodele:
- `bool checkQuantity(int)` - verfica disponibiliatea unei cantitati in stoc
- `void decreaseQuantity(int)` - reduce cantitatea stocului disponibil
- `void increasaeQuantity(int)` - mareste cantitatea stocului disponibil.

Clasa `DiscountedProduct` contine, in plus, o metoda pentru a determina pretul dupa aplicarea reducerii, `float priceAfterDiscount()`.

### Ierarhia User

!(user_uml.jpg)

Clasa `User` este una abstracta, care reprezinta schita celor 2 tipuri de utilizatori: `BasicUser` si `PremiumUser`. Astfel, reusim sa distingem tipurile de useri prin diferite campuri/metode, oferind posibilitatea particularizarilor.

Atributele `billingData` si `deliveryData` din clasa `User` sunt obiecte de tipul `Address`, clasa aflata in relatie de agregare.

Clasa `PremiumUser` este caracterizata de:
- atributul `discounts`, un  map de tipul `<int productID, int discount>` ce contine reduceri pentru diferite produse
- atributul `premiumSubscriptionCost`, costul abonamentului premium.

Clasa `BasicUser` contine un singur atribut aditional, `float costTransport`, pretul transportului produselor.

Pentru clasa `Address` au fost implementate urmatoareale metode:
- constructori cu si fara parameterii, dar si constructor de copiere
- gettere si settere pentru atribute
- supradefinirea operatorului de atribuire
- supradefinirea operatorilor de egalitate, respectiv inegalitate
- supradefinirea operatorului de afisare.

Toate clasele din ierarhia `User` contin constructori cu si fara parametri, constructori de copiere, supradefinirea operatorului de atribuire, gettere, respectiv settere pentru atributele  membre.

Clasa abstracta `User` mai contine si:
- un destructor virtual
- metoda virtuala `string getUserType()` pentru a determina tipul utilizatorului
- metoda virtuala `float getTransportCost()` ce returneaza pretul transportului in functie de tipul utilizatorului (`transportCost` pentru 
`BasicUser`, respectiv 0 pentru `PremiumUser`)
- metoda virtuala `void displayUser()` pentru afisarea atributelor utilizatorului
- metoda virtuala `json toJSON()`.

### Clasa ShoppingCart 

Pentru buna functionare a sistemului, este nevoie, evident, de un cos de produse. Clasa `ShoppingCart` contine 2 atribute:
- `map<int, int> shoppingCart` - ce reprezinta cosul de produse propriu-zis, o colectie de perechi **(Product ID, Quantity)**
- `string payMethod` - metoda de plata.

Metodele implementate pentru aceasta clasa sunt:
- constructor fara parametri
- constructor cu un singur parametru, `payMethod`
- gettere, respectiv settere pentru atribute
- `void addProduct(int id, int quantity)` - adauga `quantity` produse cu id-ul `id` in cosul de cumparaturi (in limita stocului disponibil)
- `void deleteProduct(int productID)` - elimina produsul cu `productID` din cos (in cazul in care se gaseste)
- `void raiseQuantity(int id, int quantity)` - creste cantitatea produsului caracterizat de `productID` cu `quantity` unitati (in limita stocului)
- `void lowerQuantity(int id, int quantity)` - asemenea metodei de  mai sus, doar ca de data aceasta reducem cantitatea.
- `void displayShoppingCart()` - afiseaza cosul de produse
- `json toJSON`.

### Clasa Server

Clasa `Server` este componenta ce leaga datele utlizatorilor si ale produselor. Vom instantia un singur obiect al acestei clase: `server`. (vom implementa un **singleton**).

Clasa contine urmatoarele atribute:
- `static Server *instance` - unica instanta a clasei
- `int usersCapacity` - capacitatea de utilizatori a serverului
- `list<User *> usr` - lista tuturor utilizatorilor din cadrul serverului 
- `list<Product *> prod` - lista tuturor produselor din cadrul serverului
- `map<int, ShoppingCart *>  __UserID__ProductsCart__` - un map a carui cheie este ID-ul utilizatorului, iar valoarea este un pointer catre cosul sau de produse.

Metodele implementate pentru aceasta clasa sunt:
- constructorul privat fara parametri si destructorul public
- metoda statica `Server* GetInstance()` ce creeaza (in cazul in care nu exista) si returneaza adresa instantei `Server`
- gettere si settere pentru `__UserID__ProductsCart__`, `usr` si `prod`
- `void populateProducts(const json &)` - populeaza `prod` cu produsele din parametrul de tip `json`
- `void populateUsers(const json &)` - similar cu metoda precedenta, dar pentru utilizatori
- `bool requestAddProduct(int userID, int productID, int quantity)` - verifica daca exista cantitatea necesara pentru a adauga produsul cu `productID` in cosul utilizatorului cu `UserID`. In cazul in care exista cel putin `quantity` produse in stoc, metoda adauga produsul in cosul utilizatorului (sau modifica cantitatea) si modifica stocul ramas in magazin, In cazul in care s-a reusit operatia, rezultatul returnat va fi `true`, altfel metoda va returna `false`.
- `bool requestDeleteProduct(int userID, int productID, int quantity)` - functioneaza similar cu metoda descrisa deasupra, doar ca elimina canitatea `quantity` de `productID` din cosul utilizatorului `userID` (in cazul in care `quantity` este mai mare sau egal decat cantitatea prezenta in cos, produsul se va elimina complet). In cazul efectuarii cu succes a operatiei se va returna `true`, altfel `false`.

### Clasa LRU Cache

Pentru optimizarea procedurilor de adaugare, eliminare produse, vom simula comportamentul unui 'Least Recently Used Cache', retine ID-ul produselor ce reprezinta ultimele accesari ale utilizatorilor.

Clasa este formata din 3 atribute:
- `size` de tipul `unsigned int` - dimensiunea actuala a LRU Cache-ului
- `capacity` de acelasi tip - dimensiunea maxima a Cache-ului
- `lru` de tipul `vector<int>` - vectorul din spatele cache-ului ce contine id-urile produselor.

Metodele implementate pentru aceasta clasa:
- constructor cu un singur parametru `capacity`
- gettere si settere pentru atribute
- `vector<int> processRequests(vector<int> requestsNo)` - metoda primeste ca parametru un vector de ID-uri ale produselor solicitate si returneaza stadiul final al cache-ului dupa efectuarea solicitarlior.

### Clasa QuerySolver

Clasa contine metodele ce vor rezolva interogarile aferente cerintei 3 din tema.

Cele 6 metode sunt:
- `list<Product*> Query_3a()` - in cadrul metodei se parcurge lista de produse a serverului si se adauga intr-o noua lista produsele de tipul `Basi○User` din categoria `espressor`. Noua lista va fi returnata de metoda.
- `list<User*> Query_3b()` - in cadrul metodei se parcurge lista de produse a serverului si se adauga intr-o noua lista utilizatorii de tipul `DiscountedProduct` ce au un cost al transportului `<= 11.5`. Noua lista va fi returnata de metoda.
- `list<Product*> Query_3c()` - metoda returneaza o lista rezultata in urma parcurgerii listei de produse si selectarea produselor de tipul `ResealedProduct` ce au in campul `reason` motivul `lipsa accesorii`. Inainte de functia `return` lista este sortata crescator dupa pretul produselor.
- `list<Product*> Query_3d()` - metoda returneaza o lista rezultata in urma parcurgerii listei de produse si selectarea produselor de tipul `FoodProduct`. Inainte de functia `return` lista este sortata crescator dupa `name`, `countryOfOrigin` si `leiPerKg`.
- `list<User*> Query_3e()` - in cadrul metodei se apeleaza metoda statica `getMostPopularCounty` din clasa `Utility` pentru a obtine judetul cel mai populat. In continuare, se va parcurge lista de utilizatori pentru a gasi utilizatorii din acest judet, care locuiesc la casa, acestia vor fi adaugati intr-o noua lista. In final, se va sorta noua lista dupa `ID` si se va returna.
- `list<User*> Query_3f()` - in cadrul metodei se apeleaza metoda statica `getPhonesAndPrintersIDs` din clasa `Utility` pentru a obtine o lista cu ID-urile telefoanelor si imprimantelor. In continuare, se va itera prin lista de utilizatori si, in cazul utilizatorilor premium, se vor cauta ID-urile din lista generata mai sus printre discount-urile utilizatorului curent. In cazul gasirii unui produs, utilizatorul va fi adaugat in lista returnata de metoda.

Pentru realizarea interogarilor, s-au folosit mai multe metode ajutatoare din clasa `Utility`. Aceasta clasa contine urmatoarele metode statice:
- `bool comparePrice(Product*, Product*)` - utila pentru sortarea in functie de pret a unei liste de tipul `list<Product*>`
- `bool compareFoodProduct(Product*, Product*)` - utila pentru sortarea in functie de `name`, `countryOfOrigin` si `leiPerKg` a unei liste de tipul `list<Product*>` ce contine produse alimentare
- `bool compareUID(const User*, const User*)` - utila pentru sortarea in functie de ID a unei liste de tipul `list<User*>`
- `string getMostPopularCounty(list<User*>)` - returneaza cel mai populat judetul cu cei mai multi utilizatori din lista data ca parametru
- `list<int> getPhonesAndPrintersIDs(list<Product*>)` - returneaza o lista cu ID-urile imprimantelor si telefoanelor din lista furnizata ca parametru
- `bool isHouse(Address)` - verifica daca o adresa corespunde unei case


