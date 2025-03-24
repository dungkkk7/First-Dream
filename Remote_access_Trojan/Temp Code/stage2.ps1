function Get-RandomText {
    param (
        [int]$Length = 10  # Default length of the random text
    )
    
    # Define the characters to choose from
    $characters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"
    
    # Generate random text by picking characters randomly and joining them
    $randomText = -join ((0..($Length-1)) | ForEach-Object { $characters[(Get-Random -Maximum $characters.Length)] })
    
    return $randomText
}
#$env:temp là biến môi trường trong Windows, trỏ đến thư mục tạm của người dùng (thường là C:\Users\<username>\AppData\Local\Temp). 
# Chuyển đến thư mục tạm
Set-Location $env:temp

# Tạo tên thư mục ngẫu nhiên
$dirName = Get-RandomText

# Tạo thư mục mới
mkdir $dirName