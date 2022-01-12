# cpp-parser

Тестовое задание. Парсер выражений похожих на JSON.
Примеры входных данных в папке bin.

Вход:
```
shape = {
type = "tetrahedron"
vertices = {
point = { x = "1" y = "0" z = "0" }
point = { x = "0" y = "1" z = "0" }
point = { x = "0" y = "0" z = "1" }
point = { x = "1" y = "1" z = "1" }
}
color = { r = "0xFF" g = "0x00" b = "0x80" alpha = "0x80" }
}
```

Выход:
```
< id: 0; parentid: null; name: shape; value: 1 2 19 >
  < id: 1; parentid: 0; name: type; value: "tetrahedron" >
  < id: 2; parentid: 0; name: vertices; value: 3 7 11 15 >
    < id: 3; parentid: 2; name: point; value: 4 5 6 >
      < id: 4; parentid: 3; name: x; value: "1" >
      < id: 5; parentid: 3; name: y; value: "0" >
      < id: 6; parentid: 3; name: z; value: "0" >
    < id: 7; parentid: 2; name: point; value: 8 9 10 >
      < id: 8; parentid: 7; name: x; value: "0" >
      < id: 9; parentid: 7; name: y; value: "1" >
      < id: 10; parentid: 7; name: z; value: "0" >
    < id: 11; parentid: 2; name: point; value: 12 13 14 >
      < id: 12; parentid: 11; name: x; value: "0" >
      < id: 13; parentid: 11; name: y; value: "0" >
      < id: 14; parentid: 11; name: z; value: "1" >
    < id: 15; parentid: 2; name: point; value: 16 17 18 >
      < id: 16; parentid: 15; name: x; value: "1" >
      < id: 17; parentid: 15; name: y; value: "1" >
      < id: 18; parentid: 15; name: z; value: "1" >
  < id: 19; parentid: 0; name: color; value: 20 21 22 23 >
    < id: 20; parentid: 19; name: r; value: "0xFF" >
    < id: 21; parentid: 19; name: g; value: "0x00" >
    < id: 22; parentid: 19; name: b; value: "0x80" >
    < id: 23; parentid: 19; name: alpha; value: "0x80" >
```

Параметры:
1) путь до входного файла
2) путь до выходного файла (создаст, если нет)
