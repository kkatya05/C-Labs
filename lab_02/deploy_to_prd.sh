#!/bin/bash
echo "🚀 Начинаю деплой на PRODUCTION (prd)..."

# Переключаемся на ветку prd
git checkout prd

# Накатываем изменения из dev
git merge dev

# Отправляем обновленный prd на GitHub
git push origin prd

# Возвращаемся в рабочую ветку dev
git checkout dev

echo "✅ Успешно! Ветка prd обновлена."