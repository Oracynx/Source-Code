#!/usr/bin/env bash
set -euo pipefail

# 计算前一天日期（UTC+8 时区）
YESTERDAY=$(TZ=Asia/Shanghai date -d 'yesterday' '+%Y-%m-%d')
LOG_FILE="${YESTERDAY}.md"

# 获取当天 00:00–23:59:59 的提交记录
GIT_LOG=$(git log \
  --since="${YESTERDAY} 00:00:00" \
  --until="${YESTERDAY} 23:59:59" \
  --pretty=format:"- %h %ad %an: %s" \
  --date=iso)

if [[ -z "${GIT_LOG}" ]]; then
  echo "[$YESTERDAY] 无提交，退出。"
  exit 0
fi

# 调用 DeepSeek API
RESPONSE=$(python3 - <<EOF
import os, requests, json

url = os.environ['DEEPISEEK_API_URL']
headers = {
    'Content-Type': 'application/json',
    'Authorization': f"Bearer {os.environ.get('DEEPISEEK_API_KEY','')}"
}
payload = {
    'prompt': os.environ['DEEPISEEK_PROMPT'],
    'text': """${GIT_LOG}"""
}
resp = requests.post(url, headers=headers, json=payload)
resp.raise_for_status()
print(resp.json().get('result',''))
EOF
)

# 写入 Markdown
{
  echo "# 提交摘要 — ${YESTERDAY}"
  echo
  echo "${RESPONSE}"
} > "${LOG_FILE}"
