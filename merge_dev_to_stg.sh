#!/bin/bash
git checkout stg
git pull origin stg
git merge dev --no-ff
TAG_NAME="stg-$(date +%Y%m%d-%H%M%S)"
git tag "$TAG_NAME"
git push origin stg
git push origin "$TAG_NAME"
git checkout dev
echo "Перенос из dev в stg выполнен. Тег: $TAG_NAME"
