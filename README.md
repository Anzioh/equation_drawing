# equation_drawing

## API

### 新增方程式

addEquation {hash} {equation}

```json
{
    "id": 1, // 如果 isError 為 true 則回傳 -1
    "equation": "y=x+1",
    "isError": false,
    "errorMessage": "msg",
    "hash": "hash"
}
```

### 修改方程式

editEquation {hash} {id} {equation}

```json
{
    "id": 1,
    "srcEquation": "y=1",
    "equation": "y=x+1",
    "isError": false,
    "errorMessage": "msg",
    "hash": "hash"
}
```

### 取得方程式線上的座標

getLine {hash} {id} {dpi} {xMin} {xMax} {yMin} {yMax}

```json
{
    "x": [1, 2, 3, 4, 5],
    "y": [1, 2, 3, 4, 5],
    "hash": "hash"
}
```

### 取得所有方程式的線上的座標

getAllLine {hash} {dpi} {xMin} {xMax} {yMin} {yMax}

```json
{
    "equations": [
        {
            "id": 1,
            "x": [1, 2, 3, 4, 5],
            "y": [1, 2, 3, 4, 5]
        },
        {
            "id": 2,
            "x": [1, 2, 3, 4, 5],
            "y": [1, 2, 3, 4, 5]
        }
    ],
    "hash": "hash"
}
```

### 刪除方程式

delEquation {hash} {id}

```json
{
    "isError": false,
    "errorMessage": "",
    "hash": "hash"
}
```

### 新增變數

addVar {hash} {equation}

```json
{
    "id": 1,
    "isError": false,
    "equation": "a=1",
    "errorMessage": "",
    "hash": "hash"
}
```

### 編輯變數

editVar {hash} {id} {equation}

```json
{
    "id": 1,
    "srcEquation": "a=1",
    "equation": "a=1+2",
    "isError": false,
    "errorMessage": "",
    "hash": "hash"
}
```

### 刪除變數

delVar {hash} {id}

```json
{
    "isError": false,
    "errorMessage": "",
    "hash": "hash"
}
```

### API Factory(for GUI test)

apiTest {hash} {content}

```json
{
    "hash": "...",
    "content": "..."
}
```
