#!/bin/bash
echo "🚀 Начинаю деплой на STAGE (stg)..."

# Переключаемся на ветку stg
git checkout stg

# Накатываем изменения из dev
git merge dev

# Отправляем обновленный stg на GitHub
git push origin stg

# Возвращаемся в рабочую ветку dev
git checkout dev

echo "✅ Успешно! Ветка stg обновлена."