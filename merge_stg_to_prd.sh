#!/bin/bash
git checkout prd
git pull origin prd
git merge stg --no-ff
TAG_NAME="prd-$(date +%Y%m%d-%H%M%S)"
git tag "$TAG_NAME"
git checkout dev
echo "Перенос из stg в prg выполнен. Тег: $TAG_NAME"
