# מטלה 1 - גרפים (Classes and Namespaces)

נטע כהן netaco432@gmail.com 32519774

במטלה זו מימשתי מחלקת גרף המייצגת גרף באמצעות מטרוצת שכנויות הממומשת ע"י vector<vector<int>>.
שדה פרטי נוסף שהוספתי למחלקה הוא n, על מנת שאוכל לשלוף את מספר קדקדי הגרף בקלות.
המחלקה גרף מכילה פונקציות get לשני השדות הפרטיים, פונקציית הדפסה ופונקציית טעינת גרף.

בנוסף יצרתי מחלקת Algorithm למימוש אלגוריתמים שונים על גרפים:

- `isConnected(g)` - האלגוריתם מקבל גרף ומחזיר 1 אם הגרף קשיר (אחרת מחזיר 0).
באלגוריתם זה השתמשתי בפונקציית עזר העוברת על המערך בBFS ומסמנת את הקדקדים שפגשנו, ומחזירה האם אכן עברנו על כולם.
מכיוון שגרף יכול להיות מכוון, בפונקצייה isconnected BFS פעמיים, משני קדקדים שונים, וכך אני יכולה לדעת שמגיעים לכל הקדקדים גם בגרפים מכוונים. 
קראתי ל

- `shortestPath(g,start,end)` - האלגוריתם מקבל גרף, קודקוד התחלה וקודקוד סיום ומחזיר את המסלול הקל ביותר (במקרה שהגרף לא ממושקל - הקצר ביותר) בין שני הקודקודים. במידה ואין מסלול כזה, האלגוריתם מחזיר -1.
באלגוריתם זה השתמשתי בפונקציית עזר המממשת את אלגוריתם dijkstra למציאת מסלולים קצרים מקדקד מסוים לשאר קדקדי הגרף. הפונקצייה משתמשת בתור קדימויות למציאת המסלול הקצר ביותר, ושומרת את ה"אבא" של כל קדקד על מנת לשחזר בקלות את המסלול שעברנו על מנת להגיע אליו.

- `isContainsCycle(g)` - האלגוריתם מקבל גרף ומדפיס מעגל כלשהו. אם לא קיים מעגל בגרף, האלגוריתם מחזיר 0.
האלגוריתם משתמש בפונקציית עזר dfs שעוברת על הגרף בחיפוש לעומק תוך סימון קדקדים שביקרנו בהם וקדקדי "אב", כך שכשנתקלים בקדקד שסומן כבר המסקנה היא שסגרנו מעגל, ונשאר רק לשחזר את קדקדיו באמצות קדקדי האב ששמרנו.

- `isBipartite(g)` - האלגוריתם מקבל גרף ומחזיר את החלוקה של הגרף לגרף דו-צדדי. אם אי אפשר לחלק את הגרף, האלגוריתם מחזיר 0.
למימוש אלגוריתם זה "צבעתי" את הקדקדים בשיטתיות ב2 צבעים כך ששכנים לא יצבעו באותו צבע. אם קרה ששכנים כן נצבעו באותו צבע כתוצאה מאילוצי שכנויות אחרות אז מוצזר שהגרף אינו ניתן לחלוקה דו צדדית. אחרת, מוחזרות קבוצות החלוקה האפשרית.

- `negativeCycle(g)` - האלגוריתם מקבל גרף ובודק האם קיים מעגל שלילי (כלומר מעגל שסכום המשקלים של הצלעות שלילי). 
בפונקצייה זו השתמשתי באלגוריתם בלמן-פורד למציאת מעגלים שליליים. האלגוריתם עושה "relax" v-1 פעמים וכך מוצא את המסלולים הקצרים ביותר מקדקד מסוים לכל צלע בגרף, ואז עושה סיבוב נוסף על הצלעות ובודק האם פעולת "relax" נוספת אפשרית. אם כן - קיים בגרף מעגל שלילי, ואחרת לא קיים.


הוראות הרצת התוכנית:
- על מנת להריץ את קובץ הדמו
make demo
make run
- על מנת להריץ את קובץ הטסטים
make test
./test


  
