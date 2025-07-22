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

# 调用 OpenAI（DeepSeek）API
RESPONSE=$(python3 - <<'EOF'
import os, requests, subprocess

url       = os.environ['DEEPSEEK_API_URL']
api_key   = os.environ['DEEPSEEK_API_KEY']
prompt    = os.environ['DEEPSEEK_PROMPT']
model     = os.environ.get('DEEPSEEK_MODEL', 'gpt-3.5-turbo')

git_log = subprocess.check_output(
    ["bash", "-lc", "printf \"%s\" \"$GIT_LOG\""],
    universal_newlines=True
)

payload = {
    "model": model,
    "messages": [
        {"role": "system", "content": prompt},
        {"role": "user",   "content": git_log}
    ]
}
headers = {
    "Authorization": f"Bearer {api_key}",
    "Content-Type":  "application/json",
}

resp = requests.post(url, headers=headers, json=payload)
resp.raise_for_status()
print(resp.json()['choices'][0]['message']['content'])
EOF
)

# 写入 Markdown
{
  echo "# 提交摘要 — ${YESTERDAY}"
  echo
  echo "${RESPONSE}"
} > "${LOG_FILE}"