int contactbyname(Contact * a,Contact * b);
int contactbyphone(Contact * a,Contact * b);
int contactbyemail(Contact * a,Contact * b);

void bubble_sort(AddressBook *addressBook, int (*cmp)(Contact *,Contact *));